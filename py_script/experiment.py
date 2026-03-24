import subprocess

config_file = ["sample.json"]

for conf in config_file:
    
    subprocess.run(["./aco","config_json/" + conf])
    subprocess.run(["python3","script/mapping.py", "config_json/" + conf])

print("batch experiments completed")