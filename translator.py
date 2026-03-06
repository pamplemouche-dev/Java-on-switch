import os
import zipfile

def run_bot():
    jar_path = "romfs/server.jar"
    output_cpp = "minecraft_server_native.cpp"
    
    with open(output_cpp, "w") as f:
        f.write("#include <switch.h>\n")
        f.write("#include <stdio.h>\n\n")
        
        f.write("// --- CODE SERVEUR TRADUIT ---\n")
        f.write("extern \"C\" void start_minecraft_core() {\n")
        f.write("    printf(\"Serveur Natif : Charge\\n\");\n")
        f.write("}\n\n")
        
        f.write("// --- CHARGEUR DE MODS SD CARD ---\n")
        f.write("extern \"C\" void load_sd_mods() {\n")
        f.write("    printf(\"Recherche de mods sur /switch/mods/...\\n\");\n")
        f.write("}\n")

if __name__ == "__main__":
    run_bot()
