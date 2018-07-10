#ifdef _MSC_VER

#include <windows.h>

extern "C"
int WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /* lpReservedt */)
{
   (void)hInstance;
   switch (dwReason)
   {
      case DLL_PROCESS_ATTACH:   ::OutputDebugStringA("dll2.DllMain() ---> DLL_PROCESS_ATTACH\n");  break;
      case DLL_PROCESS_DETACH:   ::OutputDebugStringA("dll2.DllMain() ---> DLL_PROCESS_DETACH\n");  break;
      case DLL_THREAD_ATTACH:    ::OutputDebugStringA("dll2.DllMain() ---> DLL_THREAD_ATTACH\n");   break;
      case DLL_THREAD_DETACH:    ::OutputDebugStringA("dll2.DllMain() ---> DLL_THREAD_DETACH\n");   break;
   }

   return 1;
}

#endif // _MSC_VER
