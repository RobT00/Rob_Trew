import os
import tempfile
import shutil
import pandas as pd
import numpy as np
import sklearn as sk


FILES = {
    "submission": {
        "random": "tcd ml 2019-20 income prediction submission file example (random solutions).csv",
        "use": "tcd ml 2019-20 income prediction submission file.csv"
    },
    "test": "tcd ml 2019-20 income prediction test (without labels).csv",
    "training": "tcd ml 2019-20 income prediction training (with labels).csv"
}


def get_data(path):
    if not path:
        raise FileNotFoundError("{} not found".format(path))
    data = pd.read_csv(path)
    return data


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

    # cleanup(script_dir)
