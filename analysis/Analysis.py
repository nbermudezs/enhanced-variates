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

    @staticmethod
    def plot(data):
        table = data['statistics']['frequencyTable']
        scores = np.array([x['key'] for x in table])
        counts = np.array([x['value'] for x in table])
        plt.bar(scores, counts)
        plt.show()

        Analysis.boxplot(scores, counts)
        Analysis.plot_top_k(scores, counts, 10)
        Analysis.plot_top_quantile(scores, counts, 0.1)

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
