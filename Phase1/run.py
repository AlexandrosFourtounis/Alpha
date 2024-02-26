import subprocess
subprocess.run(["flex", "--outfile=al.c", "al.l"], check=True)
subprocess.run(["gcc", "-o", "al", "al.c"], check=True)