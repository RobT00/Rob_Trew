import os
import tempfile
import shutil
import pandas as pd
import numpy as np
import sklearn as sk

FILE_FORMAT = "csv"

FILES = {
    "submission": {
        "random": "tcd ml 2019-20 income prediction submission file example (random solutions).{}".format(FILE_FORMAT),
        "use": "tcd ml 2019-20 income prediction submission file.{}".format(FILE_FORMAT)
    },
    "test": "tcd ml 2019-20 income prediction test (without labels).{}".format(FILE_FORMAT),
    "training": "tcd ml 2019-20 income prediction training (with labels).{}".format(FILE_FORMAT)
}


def get_data(path):
    if not path:
        raise FileNotFoundError("{} not found".format(path))
    data = pd.read_csv(path)
    return data


def process(df):
    """
    To manipulate the training data
    :param df: pandas dataframe
    :return:
    """

    """
    1. Instance - Instance of data (irrelevant)

    2. Year of Record -  Year record was made (possibly unimportant) - scale on max/min
    3. Gender - Participant gender (relevant) - encode -> (male) (female) (other) - "Bad" -> (other)
    4. Age - Age of participant (relevant) - scale on min/max
    5. Country - Country participant is from/works in (relevant) - use ISO country code ?
    6. Size of City - Population size (somewhat relevant) - scale from ISO ? Aggregate with country in some way ?
    7. Profession - Participant job (relevant) - try to categorise (use salary as metric) ?
    8. University Degree - Level of education - encode -> (no) (bachelor) (master) (phd) - "Bad" -> (no)
    9. Wears Glasses - Boolean glasses wearing (possibly unimportant, age correlated ?) - encode (already ?) -> (no) (yes) - "Bad" -> (no)
    10. Hair Colour - Hair (possible relevant) - encode ? RGB ? - "Bad" -> bald ?
    11. Body height [cm] - Tallness (relevant) - scale to meters?

    12. Income in EUR - income - leas as is - desired output
    :return:
    """
    l = len(df)
    # instance = df.iloc[:, 0]
    instance = df["Instance"]

    # year_record = df.iloc[:, 1]
    year_record = df["Year of Record"]
    # gender = df.iloc[:, 2]
    gender = df["Gender"]
    # age = df.iloc[:, 3]
    age = df["Age"]
    # country = df.iloc[:, 4]
    country = df["Country"]
    # population = df.iloc[:, 5]
    population = df["Size of City"]
    # job = df.iloc[:, 6]
    job = df["Profession"]
    # degree = df.iloc[:, 8]
    degree = df["University Degree"]
    # glasses = df.iloc[:, 9]
    glasses = df["Wears Glasses"]
    # hair = df.iloc[:, 10]
    hair = df["Hair Color"]
    # height = df.iloc[:, 11]
    height = df["Body Height [cm]"]

    # income = df.iloc[:, 12]
    income = df["Income in EUR"]

    return


def cleanup(return_dir):
    cwd = os.getcwd()
    os.chdir(return_dir)
    shutil.rmtree(cwd)
    if os.path.exists(cwd):
        raise FileExistsError("{} exists".format(tmp_dir))
    os.chdir(return_dir)


if __name__ == '__main__':
    script_dir = os.getcwd()
    root_dir = os.path.dirname(script_dir)
    os.chdir(root_dir)
    data_dir = os.path.join(root_dir, "Data")
    if os.path.exists(data_dir):
        print(data_dir)
    # tmp_dir = tempfile.mkdtemp(dir=root_dir)

    tmp_dir = os.path.join(root_dir, "tmp")
    if os.path.exists(tmp_dir):
        shutil.rmtree(tmp_dir)
    os.makedirs(tmp_dir)

    os.chdir(data_dir)
    training_file = shutil.copy(FILES.get("training"), tmp_dir)
    os.chdir(tmp_dir)
    training_data = get_data(training_file)
    process(training_data)

    # cleanup(script_dir)