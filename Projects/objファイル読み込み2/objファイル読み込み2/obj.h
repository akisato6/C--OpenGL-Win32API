
#include "PNG.h"

using namespace std;
//3つのベクトル
struct Vector3f{
	float x;
	float y;
	float z;
}vec3d;
//4つのベクトル
struct Vector4f{
	float x;
	float y;
	float z;
	float w;
}vec4d;
//4つのカラー
struct Color4{
	float r;
	float g;
	float b;
	float a;
};
//4つの反射
struct Reflection4{
	Color4 diffuse;
	Color4 ambient;
	Color4 emission;
	Color4 specular;
};
//UV座標
struct UV{
	float u;//u値
	float v;//v値
}vec2d;
struct Vector4I{
	int x;
	int y;
	int z;
	int w;
};
//ポリゴンデータ
struct Triangle{
	Vector3f TriVer;
	Vector3f TriNor;
	UV TriUV;
}Tri;
//ポリゴンデータ
struct Quadrangle{
	Vector3f QuadVer;
	Vector3f QuadNor;
	UV QuadUV;
}Quad;
//マテリアル構造体
struct MATERIAL{
	string MaterialName;//マテリアル名
	Reflection4 MaterialColor;//反射
	float Shininess;//shininess
	string TextureName;//テクスチャ名
	int TexNo;//テクスチャNO.
	vector <Triangle> Tridata;//三角面データ
	vector <Quadrangle> Quaddata;//四角面データ
	vector <unsigned int> TriVerID;//各種インデックス
	vector <unsigned int> TriNorID;
	vector <unsigned int> TriUVID;
	vector <unsigned int> QuadVerID;
	vector <unsigned int> QuadNorID;
	vector <unsigned int> QuadUVID;
}mtl;
//モデルクラス
class MODEL{
protected:
	bool LoadMaterialFromFile(char* FileName);//マテリアルロード
	vector <MATERIAL> Material;
	vector <TEXTURE*> TexData;//テクスチャデータ
	vector<GLuint> TexID;//テクスチャID
	GLuint TexID2;
	TEXTURE* tex;
public:
	MODEL();
	MODEL(char* FileName);//コンストラクタ
	bool OBJ_Load(char* FileName);//ロード
	void Draw();
};
MODEL::MODEL(){
}
MODEL::MODEL(char* FileName){
	OBJ_Load(FileName);
}
//描画
void MODEL::Draw(){
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	for (int i = 0; i<(signed)Material.size(); i++){
		glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (const GLfloat *)&Material[i].MaterialColor.ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (const GLfloat *)&Material[i].MaterialColor.diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (const GLfloat *)&Material[i].MaterialColor.specular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, Material[i].Shininess);
		if (Material[i].TexNo>0){
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, TexID[Material[i].TexNo - 1]);
		}
		else{
			glDisable(GL_TEXTURE_2D);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		}
		if (Material[i].Tridata.size()>1){
			glVertexPointer(3, GL_FLOAT, sizeof(Tri), &Material[i].Tridata[0].TriVer.x);
			glNormalPointer(GL_FLOAT, sizeof(Tri), &Material[i].Tridata[0].TriNor.x);
			if (Material[i].TexNo>0)glTexCoordPointer(2, GL_FLOAT, sizeof(Tri), &Material[i].Tridata[0].TriUV.u);
			glDrawArrays(GL_TRIANGLES, 0, Material[i].Tridata.size());
		}
		if (Material[i].Quaddata.size()>1){
			glVertexPointer(3, GL_FLOAT, sizeof(Quad), &Material[i].Quaddata[0].QuadVer.x);
			glNormalPointer(GL_FLOAT, sizeof(Quad), &Material[i].Quaddata[0].QuadNor.x);
			if (Material[i].TexNo>0)glTexCoordPointer(2, GL_FLOAT, sizeof(Quad), &Material[i].Quaddata[0].QuadUV.u);
			glDrawArrays(GL_QUADS, 0, Material[i].Quaddata.size());
		}
		glPopMatrix();
	}
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
}

//OBJファイル読み込み
bool MODEL::OBJ_Load(char* FileName){
	Vector4I Face[3];//一時代入用
	vector <Vector3f> Vertex;//頂点
	vector <Vector3f> Normal;//法線
	vector <UV> uv;//UV

	int Material_No = 0;
	char key[255] = { 0 };
	//OBJファイルを開いて内容を読み込む
	FILE* fp = NULL;
	fopen_s(&fp, FileName, "rt");

	//読み込み
	fseek(fp, SEEK_SET, 0);

	while (!feof(fp))
	{
		//キーワード
		ZeroMemory(key, sizeof(key));
		fscanf_s(fp, "%s ", key, sizeof(key));
		//マテリアル
		if (strcmp(key, "mtllib") == 0){
			fscanf_s(fp, "%s ", key, sizeof(key));
			LoadMaterialFromFile(key);
		}
		//頂点
		if (strcmp(key, "v") == 0){
			fscanf_s(fp, "%f %f %f", &vec3d.x, &vec3d.y, &vec3d.z);
			Vertex.push_back(vec3d);
		}
		//法線
		if (strcmp(key, "vn") == 0){
			fscanf_s(fp, "%f %f %f", &vec3d.x, &vec3d.y, &vec3d.z);
			Normal.push_back(vec3d);
		}
		//テクスチャ
		if (strcmp(key, "vt") == 0){
			fscanf_s(fp, "%f %f", &vec2d.u, &vec2d.v);
			uv.push_back(vec2d);
		}
		//マテリアルセット
		if (strcmp(key, "usemtl") == 0){
			fscanf_s(fp, "%s ", key, sizeof(key));
			for (int i = 0; i<(signed)Material.size(); i++){
				if (strcmp(key, Material[i].MaterialName.c_str()) == 0)Material_No = i;
			}
		}
		//面のインデックス 0=頂点 1=UV 2=法線
		if (strcmp(key, "f") == 0){
			Face[0].w = -1;
			Face[1].w = -1;
			Face[2].w = -1;
			fscanf_s(fp, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &Face[0].x, &Face[1].x, &Face[2].x, &Face[0].y, &Face[1].y, &Face[2].y, &Face[0].z, &Face[1].z, &Face[2].z, &Face[0].w, &Face[1].w, &Face[2].w);
			if ((Face[0].w == -1) && (Face[1].w == -1) && (Face[2].w == -1)){
				//三角面
				Material[Material_No].TriVerID.push_back(Face[0].x - 1);
				Material[Material_No].TriVerID.push_back(Face[0].y - 1);
				Material[Material_No].TriVerID.push_back(Face[0].z - 1);
				Material[Material_No].TriUVID.push_back(Face[1].x - 1);
				Material[Material_No].TriUVID.push_back(Face[1].y - 1);
				Material[Material_No].TriUVID.push_back(Face[1].z - 1);
				Material[Material_No].TriNorID.push_back(Face[2].x - 1);
				Material[Material_No].TriNorID.push_back(Face[2].y - 1);
				Material[Material_No].TriNorID.push_back(Face[2].z - 1);
			}
			else{
				//四角面
				Material[Material_No].QuadVerID.push_back(Face[0].x - 1);
				Material[Material_No].QuadVerID.push_back(Face[0].y - 1);
				Material[Material_No].QuadVerID.push_back(Face[0].z - 1);
				Material[Material_No].QuadVerID.push_back(Face[0].w - 1);
				Material[Material_No].QuadUVID.push_back(Face[1].x - 1);
				Material[Material_No].QuadUVID.push_back(Face[1].y - 1);
				Material[Material_No].QuadUVID.push_back(Face[1].z - 1);
				Material[Material_No].QuadUVID.push_back(Face[1].w - 1);
				Material[Material_No].QuadNorID.push_back(Face[2].x - 1);
				Material[Material_No].QuadNorID.push_back(Face[2].y - 1);
				Material[Material_No].QuadNorID.push_back(Face[2].z - 1);
				Material[Material_No].QuadNorID.push_back(Face[2].w - 1);
			}
		}
	}
	for (int j = 0; j<(signed)Material.size(); j++){
		for (int i = 0; i<(signed)Material[j].TriVerID.size(); i++){
			Tri.TriVer = Vertex[Material[j].TriVerID[i]];
			Tri.TriNor = Normal[Material[j].TriNorID[i]];
			Tri.TriUV = uv[Material[j].TriUVID[i]];
			Material[j].Tridata.push_back(Tri);
		}
		for (int i = 0; i<(signed)Material[j].QuadVerID.size(); i++){
			Quad.QuadVer = Vertex[Material[j].QuadVerID[i]];
			Quad.QuadNor = Normal[Material[j].QuadNorID[i]];
			Quad.QuadUV = uv[Material[j].QuadUVID[i]];
			Material[j].Quaddata.push_back(Quad);
		}
		Material[j].TriVerID.clear();
		Material[j].TriNorID.clear();
		Material[j].TriUVID.clear();
		Material[j].QuadVerID.clear();
		Material[j].QuadNorID.clear();
		Material[j].QuadUVID.clear();
	}
	Vertex.clear();
	Normal.clear();
	uv.clear();
	return true;
}
bool MODEL::LoadMaterialFromFile(char* FileName){
	FILE* fp = NULL;
	fopen_s(&fp, FileName, "rt");
	char key[255] = { 0 };
	bool flag = false;
	bool flag2 = false;
	ZeroMemory(&vec4d, sizeof(Vector4f));
	vec4d.w = 1.0f;
	mtl.MaterialColor.emission = (const Color4 &)vec4d;
	mtl.Shininess = 0.0f;
	mtl.TexNo = 0;

	fseek(fp, SEEK_SET, 0);

	while (!feof(fp))
	{
		//キーワード読み込み
		fscanf_s(fp, "%s ", key, sizeof(key));
		//マテリアル名
		if (strcmp(key, "newmtl") == 0)
		{
			if (flag){ Material.push_back(mtl); mtl.TexNo = 0; }
			flag = true;
			fscanf_s(fp, "%s ", key, sizeof(key));
			mtl.MaterialName = key;
			flag2 = false;
		}
		//Ka アンビエント
		if (strcmp(key, "Ka") == 0)
		{
			fscanf_s(fp, "%f %f %f", &vec4d.x, &vec4d.y, &vec4d.z);
			mtl.MaterialColor.ambient = (const Color4 &)vec4d;
		}
		//Kd ディフューズ
		if (strcmp(key, "Kd") == 0)
		{
			fscanf_s(fp, "%f %f %f", &vec4d.x, &vec4d.y, &vec4d.z);
			mtl.MaterialColor.diffuse = (const Color4 &)vec4d;
		}
		//Ks スペキュラー
		if (strcmp(key, "Ks") == 0)
		{
			fscanf_s(fp, "%f %f %f", &vec4d.x, &vec4d.y, &vec4d.z);
			mtl.MaterialColor.specular = (const Color4 &)vec4d;
		}
		//SHININESS
		if (strcmp(key, "Ns") == 0)
		{
			fscanf_s(fp, "%f", &vec4d.x);
			mtl.Shininess = vec4d.x;
		}
		//map_Kd テクスチャ
		if (strcmp(key, "map_Kd") == 0)
		{
			fscanf_s(fp, "%s ", key, sizeof(key));
			for (int i = 0; i<(signed)Material.size(); i++){
				if (strcmp(key, Material[i].TextureName.c_str()) == 0){
					flag2 = true;
					mtl.TexNo = Material[i].TexNo;
					break;
				}
			}
			if (flag2){
			}
			else{
				mtl.TextureName = key;
				//テクスチャを作成
				TexData.push_back(tex);
				TexData[TexData.size() - 1] = new TEXTURE(mtl.TextureName.c_str());;
				mtl.TexNo = TexData.size();
				TexID.push_back(TexID2);
				glGenTextures(1, (GLuint *)&TexID[TexData.size() - 1]);
				glBindTexture(GL_TEXTURE_2D, TexID[TexData.size() - 1]);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

				glEnable(GL_TEXTURE_2D);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TexData[TexData.size() - 1]->Width, TexData[TexData.size() - 1]->Height,
					0, GL_RGBA, GL_UNSIGNED_BYTE, TexData[TexData.size() - 1]->image);
				glDisable(GL_TEXTURE_2D);
			}
		}
	}
	fclose(fp);
	if (flag)Material.push_back(mtl);
	return true;
}