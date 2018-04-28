import csv
import json
import numpy as np
import os
import pandas as pd
import pdb
import tensorflow as tf

flags = tf.app.flags
FLAGS = flags.FLAGS

flags.DEFINE_string("input", None, "Path of the file to be summarized")
flags.DEFINE_string("output", None, "Path of the output file")
flags.DEFINE_bool("append", False, "Whether the output should "
                                   "be appended if file already exists")

million = 1e6
submissions = {
    2013: 8.15 * million,
    2014: 11 * million,
    2015: 11.57 * million,
    2016: 13 * million,
    2017: 19 * million,
    2018: 17.3 * million
}

scores = None
with open('../experiments/brackets/TTT/ESPN_scores.json') as f:
    scores = json.load(f)['scores']
    scores = {elem['year']: elem['rank'] for elem in scores}


def get_rank_100(year):
    return scores[year]['100']


class Summarizer:
    @staticmethod
    def _get_columns(data):
        cols = ['Year', 'RetentionP', 'MaxScore', 'InTop100', 'Expected']
        for col_i in np.arange(12, 20, 1):
            label = 'R' + str(col_i * 100)
            col = 'Bin' + str(col_i) + '_' + str(col_i + 1)
            if col in data.columns:
                cols.append(label)
        return cols

    @staticmethod
    def summary(file_path, output_file_path=None, append=False):
        data = pd.read_csv(file_path, sep=',', quoting=csv.QUOTE_NONE)
        years = data.Year.unique()
        retention_p = data.ReP.unique()

        summary = pd.DataFrame(columns=Summarizer._get_columns(data))
        for year in years:
            for p in retention_p:
                by_year = data[(data.Year == year) & (data.ReP == p)]
                max_score = by_year.MaxScore.max()
                if 'Replications' in by_year.columns:
                    replications = by_year.Replications.sum()
                else:
                    replications = by_year.Year.count() * 1e4
                total_in_top100 = by_year.Top100.sum()
                row = {
                    'Year': year,
                    'RetentionP': p,
                    'MaxScore': max_score,
                    'InTop100': total_in_top100,
                    'Expected': submissions[
                                    year] / replications * total_in_top100
                }
                for col_i in np.arange(12, 20, 1):
                    label = 'R' + str(col_i * 100)
                    col = 'Bin' + str(col_i) + '_' + str(col_i + 1)
                    if col not in data.columns:
                        continue
                    row[label] = by_year[col].sum()
                summary = summary.append(row, ignore_index=True)
        summary = summary.sort_values(by=['RetentionP', 'Year'])
        print(summary)
        if output_file_path:
            flags = 'a' if append else 'w'
            with open(output_file_path, flags) as out:
                summary.to_csv(out, sep=',', header=not append, index=False)


def main(_):
    if os.path.isdir(FLAGS.input):
        for file_name in os.listdir(FLAGS.input):
            if not file_name.endswith('.csv'):
                continue
            print('Summarizing ' + file_name)
            append = not os.path.isdir(FLAGS.output)
            output = FLAGS.output if append else (FLAGS.output + file_name)
            Summarizer.summary(FLAGS.input + file_name, output, append)
    else:
        Summarizer.summary(FLAGS.input, FLAGS.output, FLAGS.append)


if __name__ == '__main__':
    tf.app.run()