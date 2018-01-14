import numpy as np
import matplotlib.pyplot as plt


class Analysis:
    @staticmethod
    def print(data):
        table = data['statistics']['frequencyTable']
        scores = np.array([x['key'] for x in table])
        counts = np.array([x['value'] for x in table])
        print('Max:', np.max(scores))
        print('Min:', np.min(scores))
        print('Mode:', scores[np.argmax(counts)], '(%d)' % np.max(counts))
        print('Mean:', np.average(scores, weights=counts))
        # print('Quantiles from unique scores')
        # print('99 Quantile', np.percentile(scores, 99));
        # print('95 Quantile', np.percentile(scores, 95));
        # print('90 Quantile', np.percentile(scores, 90));
        # print('50 Quantile', np.percentile(scores, 50));

        print('Quantiles from all scores')
        all_scores = Analysis.weight_array(scores, counts)
        print('99 Quantile', np.percentile(all_scores, 99))
        print('95 Quantile', np.percentile(all_scores, 95))
        print('90 Quantile', np.percentile(all_scores, 90))
        print('50 Quantile', np.percentile(all_scores, 50))

    @staticmethod
    def plot(data):
        scores, counts = Analysis.as_scores_and_counts(data)
        plt.bar(scores, counts)
        plt.show()

        Analysis.boxplot(scores, counts)
        # Analysis.plot_top_k(scores, counts, 10)
        # Analysis.plot_top_quantile(scores, counts, 0.1)

    @staticmethod
    def weight_array(data, weights):
        zipped = zip(data, weights)
        weighted = []
        for i in zipped:
            for j in range(i[1]):
                weighted.append(i[0])
        return weighted

    @staticmethod
    def plot_top_k(scores, counts, k):
        plt.title('Top %d scores' % k)
        plt.xlabel('Score')
        plt.ylabel('Count')
        top_k = np.sort(scores)[-k:]
        top_k_counts = counts[np.argsort(scores)[-k:]]
        plt.bar(top_k, top_k_counts)
        plt.show()

    @staticmethod
    def plot_top_quantile(scores, counts, q):
        k = int(len(scores) * q)
        plt.title('Top %d%% scores' % (q * 100))
        plt.xlabel('Score')
        plt.ylabel('Count')
        top_k = np.sort(scores)[-k:]
        top_k_counts = counts[np.argsort(scores)[-k:]]
        plt.bar(top_k, top_k_counts)
        plt.show()

    @staticmethod
    def boxplot(scores, counts):
        plt.title('Scores boxplot')
        all_scores = Analysis.weight_array(scores, counts)
        plt.boxplot(all_scores)
        plt.show()

    @staticmethod
    def as_scores_and_counts(data):
        table = data['statistics']['frequencyTable']
        scores = np.array([x['key'] for x in table])
        counts = np.array([x['value'] for x in table])
        return scores, counts

    @staticmethod
    def compare(data_a, data_b):
        plt.title('Comparison of scores distribution')
        plt.xlabel('Score')
        plt.ylabel('Count')
        scores_a, counts_a = Analysis.as_scores_and_counts(data_a)
        scores_b, counts_b = Analysis.as_scores_and_counts(data_b)
        a = plt.scatter(scores_a, counts_a, s=2)
        b = plt.scatter(scores_b, counts_b, s=2)
        plt.legend((a, b), ('50-50', 'Enhanced'))
        plt.show()
