#include <vector>

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
//4つの反射
struct Reflection4{
	float diffuse;
	float ambient;
	float emission;
	float specular;
};
//4つのカラー
struct Color4{
	float r;
	float g;
	float b;
	float a;
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
	int MaterialID;//ID
	string MaterialName;//マテリアル名
	Color4 Color;//カラー
	Reflection4 ReflectionColor;//反射
	float Power;//shiness
	string TextureName;//テクスチャ名
}mtl;
//モデルクラス
class MODEL{
protected:
	bool LoadMaterialFromFile(char* FileName);//マテリアルロード
	vector <Triangle> Tridata;
	vector <Quadrangle> Quaddata;
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

void MODEL::Draw(){
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	if (Tridata.size()>1){
		glVertexPointer(3, GL_FLOAT, sizeof(Tri), &Tridata[0].TriVer.x);
		glNormalPointer(GL_FLOAT, sizeof(Tri), &Tridata[0].TriNor.x);
		glDrawArrays(GL_TRIANGLES, 0, Tridata.size());
	}
	if (Quaddata.size()>1){
		glVertexPointer(3, GL_FLOAT, sizeof(Quad), &Quaddata[0].QuadVer.x);
		glNormalPointer(GL_FLOAT, sizeof(Quad), &Quaddata[0].QuadNor.x);
		glDrawArrays(GL_QUADS, 0, Quaddata.size());
	}
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

//OBJファイル読み込み
bool MODEL::OBJ_Load(char* FileName){
	Vector4I Face[3];//一時代入用
	vector <Vector3f> Vertex;//頂点
	vector <Vector3f> Normal;//法線
	vector <UV> uv;//UV
	vector <unsigned int> TriVerID;
	vector <unsigned int> TriNorID;
	vector <unsigned int> TriUVID;
	vector <unsigned int> QuadVerID;
	vector <unsigned int> QuadNorID;
	vector <unsigned int> QuadUVID;

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
		//面のインデックス 0=頂点 1=UV 2=法線
		if (strcmp(key, "f") == 0){
			Face[0].w = -1;
			Face[1].w = -1;
			Face[2].w = -1;
			fscanf_s(fp, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &Face[0].x, &Face[1].x, &Face[2].x, &Face[0].y, &Face[1].y, &Face[2].y, &Face[0].z, &Face[1].z, &Face[2].z, &Face[0].w, &Face[1].w, &Face[2].w);
			if ((Face[0].w == -1) && (Face[1].w == -1) && (Face[2].w == -1)){
				//三角面
				TriVerID.push_back(Face[0].x - 1);
				TriVerID.push_back(Face[0].y - 1);
				TriVerID.push_back(Face[0].z - 1);
				TriUVID.push_back(Face[1].x - 1);
				TriUVID.push_back(Face[1].y - 1);
				TriUVID.push_back(Face[1].z - 1);
				TriNorID.push_back(Face[2].x - 1);
				TriNorID.push_back(Face[2].y - 1);
				TriNorID.push_back(Face[2].z - 1);
			}
			else{
				//四角面
				QuadVerID.push_back(Face[0].x - 1);
				QuadVerID.push_back(Face[0].y - 1);
				QuadVerID.push_back(Face[0].z - 1);
				QuadVerID.push_back(Face[0].w - 1);
				QuadUVID.push_back(Face[1].x - 1);
				QuadUVID.push_back(Face[1].y - 1);
				QuadUVID.push_back(Face[1].z - 1);
				QuadUVID.push_back(Face[1].w - 1);
				QuadNorID.push_back(Face[2].x - 1);
				QuadNorID.push_back(Face[2].y - 1);
				QuadNorID.push_back(Face[2].z - 1);
				QuadNorID.push_back(Face[2].w - 1);
			}
		}
	}
	for (int i = 0; i<(signed)TriVerID.size(); i++){
		Tri.TriVer = Vertex[TriVerID[i]];
		Tri.TriNor = Normal[TriNorID[i]];
		Tri.TriUV = uv[TriUVID[i]];
		Tridata.push_back(Tri);
	}
	printf("%d", Tridata.size());
	for (int i = 0; i<(signed)QuadVerID.size(); i++){
		Quad.QuadVer = Vertex[QuadVerID[i]];
		Quad.QuadNor = Normal[QuadNorID[i]];
		Quad.QuadUV = uv[QuadUVID[i]];
		Quaddata.push_back(Quad);
	}
	Vertex.clear();
	Normal.clear();
	uv.clear();
	TriVerID.clear();
	TriNorID.clear();
	TriUVID.clear();
	QuadVerID.clear();
	QuadNorID.clear();
	QuadUVID.clear();
	return true;
}
bool MODEL::LoadMaterialFromFile(char *FileName){
	return true;
}