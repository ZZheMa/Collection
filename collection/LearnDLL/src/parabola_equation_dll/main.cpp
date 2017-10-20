#include "windows.h"

BOOL WINAPI DllMain(HINSTANCE dll_handle,  // handle to DLL module
                    DWORD call_reason,  // reason for calling function
                    LPVOID reserved) {  // reserved
  // Perform actions based on the reason for calling.
  switch (call_reason) {
    case DLL_PROCESS_ATTACH:
      // Initialize once for each new process.
      // Return FALSE to fail DLL load.
      break;

    case DLL_THREAD_ATTACH:
      // Do thread-specific initialization.
      break;

    case DLL_THREAD_DETACH:
      // Do thread-specific cleanup.
      break;

    case DLL_PROCESS_DETACH:
      // Perform any necessary cleanup.
      break;
  }

  return TRUE;
}