#include "Configuration.hpp"

Configuration *Configuration::conf = 0x0;

Configuration* Configuration::instance () {
	if (conf == 0x0) {
		conf = new Configuration ();
		conf->UserHttpConfig = 0x0;
	}
	return conf;
}

void Configuration::setUSerConfig (Component *config) {
	if (UserHttpConfig)
		delete UserHttpConfig;
	UserHttpConfig = config;
}

Configuration::Configuration () {}

Component *Configuration::getConfigurations () const { return UserHttpConfig; }

unsigned int Configuration::keepAlive () const { return keepalive; }

Logger& Configuration::getLogger () { return logger; }

std::string Configuration::serverName () { return "WebServ1.0"; }

std::string Configuration::codeToReasonPhrase (unsigned short code) {
	static std::map<unsigned short, std::string> *ctop;
	if (!ctop) {
		ctop = new std::map<unsigned short, std::string> ();
		(*ctop)	[200] = "OK";
		(*ctop) [204] = "No Content";
		(*ctop)	[201] = "Created";
		(*ctop) [301] = "Moved Permanently";
		(*ctop)	[400] = "Bad Request";
		(*ctop) [401] = "Unauthorized";
		(*ctop) [403] = "Forbidden";
		(*ctop) [404] = "Not Found";
		(*ctop) [405] = "Method Not Allowed";
		(*ctop) [406] = "Not Acceptable";
		(*ctop) [409] = "Conflict";
		(*ctop) [411] = "Length Required";
		(*ctop) [413] = "Payload Too Large";
		(*ctop) [414] = "URI Too Long";
		(*ctop) [500] = "Internal Server Error";
		(*ctop) [501] = "Not Implemented";
	}
	return (*ctop)[code];
}

std::string Configuration::mimeType (const std::string& extension) {
	static std::map<std::string, std::string> *mime;
	if (!mime) {
		mime = new std::map<std::string, std::string> ();
		(*mime)["html"] = "text/html";
		(*mime)["htm"] = "text/html";
		(*mime)["shtml"] = "text/html";
		(*mime)["css"] = "text/css";
		(*mime)["xml"] = "text/xml";
		(*mime)["gif"] = "image/gif";
		(*mime)["jpeg"] = "image/jpeg";
		(*mime)["jpg"] = "image/jpeg";
		(*mime)["js"] = "application/javascript";
		(*mime)["atom"] = "application/atom+xml";
		(*mime)["rss"] = "application/rss+xml";
		(*mime)["mml"] = "text/mathml";
		(*mime)["txt"] = "text/plain";
		(*mime)["jad"] = "text/vnd.sun.j2me.app-descriptor";
		(*mime)["wml"] = "text/vnd.wap.wml";
		(*mime)["htc"] = "text/x-component";
		(*mime)["avif"] = "image/avif";
		(*mime)["png"] = "image/png";
		(*mime)["svg"] = "image/svg+xml";
		(*mime)["svgz"] = "image/svg+xml";
		(*mime)["tif"] = "image/tiff";
		(*mime)["tiff"] = "image/tiff";
		(*mime)["wbmp"] = "image/vnd.wap.wbmp";
		(*mime)["webp"] = "image/webp";
		(*mime)["ico"] = "image/x-icon";
		(*mime)["jng"] = "image/x-jng";
		(*mime)["bmp"] = "image/x-ms-bmp";
		(*mime)["woff"] = "font/woff";
		(*mime)["woff2"] = "font/woff2";
		(*mime)["jar"] = "application/java-archive";
		(*mime)["war"] = "application/java-archive";
		(*mime)["ear"] = "application/java-archive";
		(*mime)["json"] = "application/json";
		(*mime)["hqx"] = "application/mac-binhex40";
		(*mime)["doc"] = "application/msword";
		(*mime)["pdf"] = "application/pdf";
		(*mime)["ps"] = "application/postscript";
		(*mime)["eps"] = "application/postscript";
		(*mime)["ai"] = "application/postscript";
		(*mime)["rtf"] = "application/rtf";
		(*mime)["m3u8"] = "application/vnd.apple.mpegurl";
		(*mime)["kml"] = "application/vnd.google-earth.kml+xml";
		(*mime)["kmz"] = "application/vnd.google-earth.kmz";
		(*mime)["xls"] = "application/vnd.ms-excel";
		(*mime)["eot"] = "application/vnd.ms-fontobject";
		(*mime)["ppt"] = "application/vnd.ms-powerpoint";
		(*mime)["odg"] = "application/vnd.oasis.opendocument.graphics";
		(*mime)["odp"] = "application/vnd.oasis.opendocument.presentation";
		(*mime)["ods"] = "application/vnd.oasis.opendocument.spreadsheet";
		(*mime)["odt"] = "application/vnd.oasis.opendocument.text";
		(*mime)["pptx"] = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
		(*mime)["xlsx"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
		(*mime)["docx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
		(*mime)["wmlc"] = "application/vnd.wap.wmlc";
		(*mime)["wasm"] = "application/wasm";
		(*mime)["7z"] = "application/x-7z-compressed";
		(*mime)["cco"] = "application/x-cocoa";
		(*mime)["jardiff"] = "application/x-java-archive-diff";
		(*mime)["jnlp"] = "application/x-java-jnlp-file";
		(*mime)["run"] = "application/x-makeself";
		(*mime)["pl"] = "application/x-perl";
		(*mime)["pm"] = "application/x-perl";
		(*mime)["prc"] = "application/x-pilot";
		(*mime)["pdb"] = "application/x-pilot";
		(*mime)["rar"] = "application/x-rar-compressed";
		(*mime)["rpm"] = "application/x-redhat-package-manager";
		(*mime)["sea"] = "application/x-sea";
		(*mime)["swf"] = "application/x-shockwave-flash";
		(*mime)["sit"] = "application/x-stuffit";
		(*mime)["tcl"] = "application/x-tcl";
		(*mime)["tk"] = "application/x-tcl";
		(*mime)["der"] = "application/x-x509-ca-cert";
		(*mime)["pem"] = "application/x-x509-ca-cert";
		(*mime)["crt"] = "application/x-x509-ca-cert";
		(*mime)["xpi"] = "application/x-xpinstall";
		(*mime)["xhtml"] = "application/xhtml+xml";
		(*mime)["xspf"] = "application/xspf+xml";
		(*mime)["zip"] = "application/zip";
		(*mime)["bin"] = "application/octet-stream";
		(*mime)["exe"] = "application/octet-stream";
		(*mime)["dll"] = "application/octet-stream";
		(*mime)["deb"] = "application/octet-stream";
		(*mime)["dmg"] = "application/octet-stream";
		(*mime)["iso"] = "application/octet-stream";
		(*mime)["img"] = "application/octet-stream";
		(*mime)["msi"] = "application/octet-stream";
		(*mime)["msp"] = "application/octet-stream";
		(*mime)["msm"] = "application/octet-stream";
		(*mime)["mid"] = "audio/midi";
		(*mime)["midi"] = "audio/midi";
		(*mime)["kar"] = "audio/midi";
		(*mime)["mp3"] = "audio/mpeg";
		(*mime)["ogg"] = "audio/ogg";
		(*mime)["m4a"] = "audio/x-m4a";
		(*mime)["ra"] = "audio/x-realaudio";
		(*mime)["3gpp"] = "video/3gpp";
		(*mime)["3gp"] = "video/3gpp";
		(*mime)["ts"] = "video/mp2t";
		(*mime)["mp4"] = "video/mp4";
		(*mime)["mpeg"] = "video/mpeg";
		(*mime)["mpg"] = "video/mpeg";
		(*mime)["mov"] = "video/quicktime";
		(*mime)["webm"] = "video/webm";
		(*mime)["flv"] = "video/x-flv";
		(*mime)["m4v"] = "video/x-m4v";
		(*mime)["mng"] = "video/x-mng";
		(*mime)["asx"] = "video/x-ms-asf";
		(*mime)["asf"] = "video/x-ms-asf";
		(*mime)["wmv"] = "video/x-ms-wmv";
		(*mime)["avi"] = "video/x-msvideo";
	}
	std::map<std::string, std::string>::const_iterator it = mime->find (extension); 
	if (it != mime->cend ())
		return it->second;
	return "application/octet-stream";
}
