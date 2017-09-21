#pragma once
#include <string>
#include <memory>
#include <unordered_map>

struct ID3D11ShaderResourceView;
struct ID3D11DeviceContext;

struct TextureInfo
{
	std::string name;
	std::shared_ptr<std::vector<unsigned char> > RawData;
	int NumOwners;
	ID3D11ShaderResourceView* ResoureView;
};

class TextureManagerDX11
{
private:
	static const char* DEFAULT_TEXTURE;
	static int s_TexIDGen;
private:
	ID3D11ShaderResourceView* m_DefaultTexture;
	std::unordered_map<int, TextureInfo > m_Textures;
	std::unordered_map<std::string, int> m_LoadedTextures;
	std::shared_ptr<std::vector<unsigned char> > OpenTexture(const std::string& file, unsigned& width, unsigned& height);

public:
	~TextureManagerDX11();

	// Should be called from render thread only
	void Init();

	void LoadDefaultTexture();
	void DeleteTexture(int texID);
	int LoadTexture(const std::string& file);
	ID3D11ShaderResourceView** GetTexture(int texID);
	void OnTextureRemoved(int texID);
};