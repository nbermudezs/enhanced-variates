from Analysis import Analysis
from Reader import Reader


if __name__ == '__main__':
    data = Reader.read('../experiments/results/result311220171707.json')
    Analysis.print(data)
    Analysis.plot(data)
