#include "engine/rendering/TextureManagerDX11.h"
#include "engine/core/Engine.h"
#include "engine/rendering/RenderCommander.h"
#include "engine/rendering/RendererDX11.h"
#include <lodepng/lodepng.h>

const char* TextureManagerDX11::DEFAULT_TEXTURE = "resources/textures/loading.png";
int TextureManagerDX11::s_TexIDGen = 0;

TextureManagerDX11::~TextureManagerDX11()
{
	this->OnTextureRemoved(m_DefaultTextureID);
	assert(m_LoadedTextures.size() == 0);
	assert(m_Textures.size() == 0);
}

void TextureManagerDX11::Init()
{
	LoadDefaultTexture();
}

void TextureManagerDX11::LoadDefaultTexture()
{
	m_DefaultTextureID = ++s_TexIDGen;
	unsigned width, height;

	auto image = OpenTexture(DEFAULT_TEXTURE, width, height);
	TextureInfo info;

	// This is the default texture,
	// it shouldnt be deleted
	info.NumOwners = 1;
	info.RawData = image;
	m_Textures.insert({ m_DefaultTextureID, info });
	g_Engine->GetModule<RendererDX11>()->LoadTexture(image->data(), width, height, TextureFormat::RGBA, m_DefaultTextureID);
}

void TextureManagerDX11::DeleteTexture(int texID)
{
	auto& texInfo = m_Textures.find(texID);
	--texInfo->second.NumOwners;
	if (texInfo->second.NumOwners == 0)
	{
		g_Engine->GetModule<RenderCommanderDx11>()->DeleteTexture(texID);
	}
}

std::shared_ptr<std::vector<unsigned char> > TextureManagerDX11::OpenTexture(const std::string& file, unsigned& width, unsigned& height)
{
	if (file.substr(file.find_last_of('.') + 1) != "png")
	{
		assert(file.substr(file.find_last_of('.') + 1) != "png");
		return nullptr;
	}


	std::shared_ptr<std::vector<unsigned char> > image = std::make_shared<std::vector<unsigned char> >();
	unsigned error = lodepng::decode(*image, width, height, file);

	assert(error == 0);
	return image;
}

int TextureManagerDX11::LoadTexture(const std::string& file)
{
	const auto loadedTexIt = m_LoadedTextures.find(file);
	if (loadedTexIt != m_LoadedTextures.end())
	{
		++m_Textures.find(loadedTexIt->second)->second.NumOwners;
		return loadedTexIt->second;
	}

	unsigned width, height;
	auto image = OpenTexture(file, width, height);
	if (image == nullptr)
		return -1;
	auto renderCommander = g_Engine->GetModule<RenderCommanderDx11>();

	TextureInfo info;
	int texID = ++s_TexIDGen;
	// Set the default texture, while this one is loading
	info.ResoureView = *GetTexture(m_DefaultTextureID);

	info.NumOwners = 1;
	info.RawData = image;
	m_Textures.insert({ texID, info });

	renderCommander->CreateTexture(static_cast<uint8_t*>(image->data()), width, height, TextureFormat::RGBA, texID);
	return texID;
}

ID3D11ShaderResourceView** TextureManagerDX11::GetTexture(int texID)
{
	auto tex = m_Textures.find(texID);
	return tex == m_Textures.end() ? nullptr : &tex->second.ResoureView;
}

void TextureManagerDX11::OnTextureRemoved(int texID)
{
	m_LoadedTextures.erase(m_Textures.find(texID)->second.name);
	m_Textures.erase(texID);
}
