#include "IShader.h"
#include <rapidjson/document.h>

void IShader::DeSerializeFromJSON(const rapidjson::Value& val)
{
	if (!val.HasMember("Name"))
		assert("No name in IShader json!" && false);

	m_FileName = val["Name"].GetString();
}
