from Analysis import Analysis
from Reader import Reader


if __name__ == '__main__':
    BASE_PATH = '../experiments/results/'
    year = 2016
    file_name_a = '13012018181654result.json'
    file_name_b = '13012018171340result.json'

    data = Reader.read(BASE_PATH + str(year) + '/' + file_name_a)
    Analysis.print(data)
    Analysis.plot(data)

    enhanced = Reader.read(BASE_PATH + str(year) + '/' + file_name_b)
    Analysis.print(enhanced)
    Analysis.plot(enhanced)

    Analysis.compare(data, enhanced)
