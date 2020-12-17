#include "main.h"

void scriptHTTPGet()
{
	char data[1048576];
	data[1048575] = '\0';

	char *url = Plugin_Scr_GetString(0);

	if (url == NULL)
		return;

	ftRequest_t* r = Plugin_HTTP_Request(url, "GET", NULL, 0, "");

	if (r == NULL)
		return;

	if (r->code < 200 || r->code >= 300)
		return;
	
	strncpy(data, (const char*)r->recvmsg.data + r->headerLength, r->contentLength + 1);

	Plugin_Scr_AddString(data);
	
	Plugin_HTTP_FreeObj(r);
}

PCL int OnInit()
{
	Plugin_ScrAddFunction("HTTPS_GetString", scriptHTTPGet);

  return 0;
}

PCL void OnInfoRequest( pluginInfo_t *info )
{
	info->handlerVersion.major = PLUGIN_HANDLER_VERSION_MAJOR;
	info->handlerVersion.minor = PLUGIN_HANDLER_VERSION_MINOR;

	info->pluginVersion.major = PLUGIN_VERSION_MAJOR;
	info->pluginVersion.minor = PLUGIN_VERSION_MINOR;	
	strncpy(info->fullName, "HTTPGet Plugin", sizeof(info->fullName));
	strncpy(info->shortDescription, "Creates the HTTPS_GetString GSC function", sizeof(info->shortDescription));
	strncpy(info->longDescription, "Creates the HTTPS_GetString GSC function", sizeof(info->longDescription));
}
