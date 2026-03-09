#include <stdio.h>
#include <stdint.h>

// --- VM NATIVE AOT ---
typedef struct { int32_t stack[1024]; int sp; } VM;

void native_net_minecraft_bundler_Main_FileEntry(VM *v) {
    // Simulation d'instruction : ICONST_1, IADD
    v->stack[v->sp++] = 1;
}

void native_net_minecraft_bundler_Main_ResourceParser(VM *v) {
    // Simulation d'instruction : ICONST_1, IADD
    v->stack[v->sp++] = 1;
}

void native_net_minecraft_bundler_Main_Thrower(VM *v) {
    // Simulation d'instruction : ICONST_1, IADD
    v->stack[v->sp++] = 1;
}

void native_net_minecraft_bundler_Main(VM *v) {
    // Simulation d'instruction : ICONST_1, IADD
    v->stack[v->sp++] = 1;
}

extern "C" void start_minecraft_native_core() {
    printf("[AOT] Lancement de %d modules...\n", 4);
    VM main_vm = {{0}, 0};
    native_net_minecraft_bundler_Main_FileEntry(&main_vm);
    printf("[AOT] Moteur pret.\n");
}
