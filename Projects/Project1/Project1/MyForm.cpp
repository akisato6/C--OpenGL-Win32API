#include "MyForm.h"

using namespace opengl;
[STAThreadAttribute]
int main(){
	MyForm ^form1 = gcnew MyForm;
	form1->ShowDialog();
	return 0;
}