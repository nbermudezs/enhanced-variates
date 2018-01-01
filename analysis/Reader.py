import json


class Reader:
    def __init__(self):
        pass

    @staticmethod
    def read(path):
        with open(path) as f:
            data = json.load(f)
            return data
