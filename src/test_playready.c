#include <stdio.h>

#include <drmmanager.h>

/* ./drm.hds */
static const DRM_WCHAR drm_store_name[] = {
  ONE_WCHAR('.', '\0'), ONE_WCHAR('/', '\0'), ONE_WCHAR('d', '\0'), ONE_WCHAR('r', '\0'), ONE_WCHAR('m', '\0'),
  ONE_WCHAR('.', '\0'), ONE_WCHAR('h', '\0'), ONE_WCHAR('d', '\0'), ONE_WCHAR('s', '\0'), ONE_WCHAR('\0', '\0')
};

static const DRM_CONST_STRING drm_store = CREATE_DRM_STRING(drm_store_name);

int main() {
  DRM_RESULT dr = DRM_SUCCESS;
  DRM_APP_CONTEXT app_context = { 0, };
  DRM_BYTE opaque_buffer[MINIMUM_APPCONTEXT_OPAQUE_BUFFER_SIZE] = { 0, };
  DRM_BYTE revocation_buffer[REVOCATION_BUFFER_SIZE] = { 0, };

  ChkDR(Drm_Platform_Initialize());

  ChkDR(Drm_Initialize(&app_context, NULL, opaque_buffer, MINIMUM_APPCONTEXT_OPAQUE_BUFFER_SIZE, &drm_store));

  ChkDR(Drm_Revocation_SetBuffer(&app_context, revocation_buffer, REVOCATION_BUFFER_SIZE));

ErrorExit:
  Drm_Uninitialize(&app_context);
  Drm_Platform_Uninitialize();

  if (DRM_FAILED(dr)) {
    const DRM_CHAR* description;
    DRM_ERR_GetErrorNameFromCode(dr, &description);
    printf("==============================================\n");
    printf("============ Failed  ==> 0x%08X ==========\n", dr);
    printf("%s \n", description);
    printf("==============================================\n");
  } else {
    printf("==============================================\n");
    printf("============ Success ==> 0x%08X ==========\n", dr);
    printf("==============================================\n");
  }

  return 0;
}
