import os

github_name = input("Github username: ")
display_name = input("Display name:")

for i in range(1, 13):
    os.system(f"git clone https://github.com/MC202AB-2023s2/lab-{i:02}-{github_name}.git")
    os.chdir(f"lab{i:02}")
    
    if not os.path.isdir("solutions"):
        os.mkdir("solutions")
    os.mkdir(os.path.join("solutions", display_name))
    
    for f in os.listdir(os.path.join("..", f"lab-{i:02}-{github_name}")):
        if f.endswith(('.c', '.h', 'Makefile')):
            os.rename(f, os.path.join("solutions", display_name, f))

    os.chdir("..")
    os.system(f"rmdir /s /q lab-{i:02}-{github_name}")