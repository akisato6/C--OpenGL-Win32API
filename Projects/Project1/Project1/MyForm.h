#pragma once
#include "Header.h"
#define _USE_MATH_DEFINES //数学用定数を有効にする
#include < math.h >       //数学関数が宣言されているmath.hを読み込む

#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <stdio.h>


#define cosD(x) 10*cos(M_PI*(x)/180.0) // 度の単位を引数とする三角関数
#define sinD(x) 10*sin(M_PI*(x)/180.0)	

double PI = acos(-1.0);
double e = 2.7182818284590452354;
int draw = 0;
void Line2D(int x1, int y1, int x2, int y2, float size)
{
	glLineWidth(size);
	glBegin(GL_LINES);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glEnd();
}


namespace opengl {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MyForm の概要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクター コードを追加します
			//
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  circle;
	protected:

	private: System::Windows::Forms::Button^  cube;
	protected:

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textbox1;



	private: System::Windows::Forms::ListBox^  listBox1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
	private: System::Windows::Forms::ColorDialog^  colorDialog1;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  ファイルToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  新規作成ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  開くToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  保存ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  終了ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  編集EToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  カテゴリCToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ヘルプHToolStripMenuItem;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Button^  sphere;


	private:
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->circle = (gcnew System::Windows::Forms::Button());
			this->cube = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textbox1 = (gcnew System::Windows::Forms::TextBox());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->colorDialog1 = (gcnew System::Windows::Forms::ColorDialog());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->ファイルToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->新規作成ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->開くToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->保存ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->終了ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->編集EToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->カテゴリCToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ヘルプHToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->sphere = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// circle
			// 
			this->circle->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->circle->Cursor = System::Windows::Forms::Cursors::Hand;
			this->circle->Location = System::Drawing::Point(180, 76);
			this->circle->Name = L"circle";
			this->circle->Size = System::Drawing::Size(75, 23);
			this->circle->TabIndex = 0;
			this->circle->Text = L"circle";
			this->circle->UseVisualStyleBackColor = false;
			this->circle->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// cube
			// 
			this->cube->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->cube->Cursor = System::Windows::Forms::Cursors::Hand;
			this->cube->Location = System::Drawing::Point(180, 105);
			this->cube->Name = L"cube";
			this->cube->Size = System::Drawing::Size(75, 23);
			this->cube->TabIndex = 1;
			this->cube->Text = L"cube";
			this->cube->UseVisualStyleBackColor = false;
			this->cube->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->label1->Location = System::Drawing::Point(12, 26);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(170, 33);
			this->label1->TabIndex = 2;
			this->label1->Text = L"フーリエ変換";
			// 
			// textbox1
			// 
			this->textbox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->textbox1->Location = System::Drawing::Point(312, 27);
			this->textbox1->Name = L"textbox1";
			this->textbox1->Size = System::Drawing::Size(194, 19);
			this->textbox1->TabIndex = 4;
			this->textbox1->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox1_TextChanged);
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->ItemHeight = 12;
			this->listBox1->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"y=a", L"y=ax", L"y=ax^2" });
			this->listBox1->Location = System::Drawing::Point(35, 76);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(120, 88);
			this->listBox1->TabIndex = 5;
			this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::listBox1_SelectedIndexChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->label2->Location = System::Drawing::Point(58, 172);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(55, 19);
			this->label2->TabIndex = 6;
			this->label2->Text = L"label2";
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Location = System::Drawing::Point(35, 211);
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(120, 19);
			this->numericUpDown1->TabIndex = 7;
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->button3->Location = System::Drawing::Point(161, 236);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 8;
			this->button3->Text = L"color";
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// button4
			// 
			this->button4->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->button4->Location = System::Drawing::Point(35, 236);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(75, 23);
			this->button4->TabIndex = 9;
			this->button4->Text = L"Dialog";
			this->button4->UseVisualStyleBackColor = false;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->ファイルToolStripMenuItem,
					this->編集EToolStripMenuItem, this->カテゴリCToolStripMenuItem, this->ヘルプHToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(581, 24);
			this->menuStrip1->TabIndex = 10;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// ファイルToolStripMenuItem
			// 
			this->ファイルToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->新規作成ToolStripMenuItem,
					this->開くToolStripMenuItem, this->保存ToolStripMenuItem, this->終了ToolStripMenuItem
			});
			this->ファイルToolStripMenuItem->Name = L"ファイルToolStripMenuItem";
			this->ファイルToolStripMenuItem->Size = System::Drawing::Size(70, 20);
			this->ファイルToolStripMenuItem->Text = L"ファイル(F)";
			this->ファイルToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::ファイルToolStripMenuItem_Click);
			// 
			// 新規作成ToolStripMenuItem
			// 
			this->新規作成ToolStripMenuItem->Name = L"新規作成ToolStripMenuItem";
			this->新規作成ToolStripMenuItem->Size = System::Drawing::Size(122, 22);
			this->新規作成ToolStripMenuItem->Text = L"新規作成";
			// 
			// 開くToolStripMenuItem
			// 
			this->開くToolStripMenuItem->Name = L"開くToolStripMenuItem";
			this->開くToolStripMenuItem->Size = System::Drawing::Size(122, 22);
			this->開くToolStripMenuItem->Text = L"開く";
			// 
			// 保存ToolStripMenuItem
			// 
			this->保存ToolStripMenuItem->Name = L"保存ToolStripMenuItem";
			this->保存ToolStripMenuItem->Size = System::Drawing::Size(122, 22);
			this->保存ToolStripMenuItem->Text = L"保存";
			// 
			// 終了ToolStripMenuItem
			// 
			this->終了ToolStripMenuItem->Name = L"終了ToolStripMenuItem";
			this->終了ToolStripMenuItem->Size = System::Drawing::Size(122, 22);
			this->終了ToolStripMenuItem->Text = L"終了";
			// 
			// 編集EToolStripMenuItem
			// 
			this->編集EToolStripMenuItem->Name = L"編集EToolStripMenuItem";
			this->編集EToolStripMenuItem->Size = System::Drawing::Size(60, 20);
			this->編集EToolStripMenuItem->Text = L"編集(E)";
			this->編集EToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::編集EToolStripMenuItem_Click);
			// 
			// カテゴリCToolStripMenuItem
			// 
			this->カテゴリCToolStripMenuItem->Name = L"カテゴリCToolStripMenuItem";
			this->カテゴリCToolStripMenuItem->Size = System::Drawing::Size(71, 20);
			this->カテゴリCToolStripMenuItem->Text = L"カテゴリ(C)";
			// 
			// ヘルプHToolStripMenuItem
			// 
			this->ヘルプHToolStripMenuItem->Name = L"ヘルプHToolStripMenuItem";
			this->ヘルプHToolStripMenuItem->Size = System::Drawing::Size(67, 20);
			this->ヘルプHToolStripMenuItem->Text = L"ヘルプ(H)";
			// 
			// panel1
			// 
			this->panel1->Location = System::Drawing::Point(261, 49);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(293, 210);
			this->panel1->TabIndex = 11;
			this->panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::panel1_Paint_1);
			// 
			// sphere
			// 
			this->sphere->Location = System::Drawing::Point(180, 141);
			this->sphere->Name = L"sphere";
			this->sphere->Size = System::Drawing::Size(75, 23);
			this->sphere->TabIndex = 12;
			this->sphere->Text = L"sphere";
			this->sphere->UseVisualStyleBackColor = true;
			this->sphere->Click += gcnew System::EventHandler(this, &MyForm::button1_Click_1);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(581, 301);
			this->Controls->Add(this->sphere);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->numericUpDown1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->textbox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->cube);
			this->Controls->Add(this->circle);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e)
	{
		this->textbox1->Text = "straight line";
		draw = 1;
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		this->textbox1->Text = "circle";
		draw = 2;
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		this->textbox1->Text = "cube";
		draw = 3;
	}
	private: System::Void button1_Click_1(System::Object^  sender, System::EventArgs^  e)
	{
		this->textbox1->Text = "sphere";
		draw = 4;
	}

	private: System::Void listBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
	{
		label2->Text = listBox1->SelectedItem->ToString();
	}
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) 
	{
	colorDialog1->ShowDialog();
	this->BackColor = colorDialog1->Color;
	}
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) 
	{
	Form^ Dialog = gcnew Form();
	Dialog->ShowDialog();  // モーダルダイアログとして表示
	}
private: System::Void ファイルToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
	{
	}
private: System::Void 編集EToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
	{
	}
		
 private: System::Void panel1_Paint_1(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e)
 {
	OpenGLSimpleAdapter^ GLAdapter = gcnew OpenGLSimpleAdapter(GetDC((HWND)panel1->Handle.ToPointer()));
	GLAdapter->BeginRender();
	{

		glClearColor(0, 0, 0, 0);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		/*glOrtho(-20, 20, -20,20, -1, 1);*/
		int i;
		int j;
		glColor3d(1, 1, 1);
		Line2D(-100,0 , 100, 0, 1);
		Line2D(0, -100, 0, 100, 1);
	
		

		if (draw == 1)
		{
			glColor3d(1.0, 1.0, 0.0);
			Line2D(-1, -1, 1, 1, 1);

		}
		if (draw == 2)
		{
			glColor3d(0, 1.0, 1.0);
			glBegin(GL_LINE_LOOP);
			for (double a = 0.0; a<360.0; a += 10.0){
				glVertex2d(cosD(a), sinD(a));
			}
			glEnd();


		}

		
		GLdouble vertex[][3] = {
			{ 0.0, 0.0, 0.0 },
			{ 1.0, 0.0, 0.0 },
			{ 1.0, 1.0, 0.0 },
			{ 0.0, 1.0, 0.0 },
			{ 0.0, 0.0, 1.0 },
			{ 1.0, 0.0, 1.0 },
			{ 1.0, 1.0, 1.0 },
			{ 0.0, 1.0, 1.0 }
		};
		int face[][4] = {
			{ 0, 1, 2, 3 },
			{ 1, 5, 6, 2 },
			{ 5, 4, 7, 6 },
			{ 4, 0, 3, 7 },
			{ 4, 5, 1, 0 },
			{ 3, 2, 6, 7 }
		};
		glColor3d(1.0, 1.0, 0.0);
		glBegin(GL_QUADS);
		for (j = 0; j < 6; ++j) {
			for (i = 0; i < 4; ++i) {
				glVertex3dv(vertex[face[j][i]]);
			}
		}
		glEnd();
	}
	GLAdapter->EndRender();
}


private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}


};
}
