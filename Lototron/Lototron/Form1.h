#pragma once


namespace Lototron {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;	// Для конверсии String^ в LPCTSTR

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			// Загрузить настройки
			Opt = new Options();
			char CurrentPath[200];
			GetCurrentDirectory(200,CurrentPath);
			Opt->File = std::string(CurrentPath)+"\\Lototron.cfg";
			Opt->Load();
			if(WfCommon::StrToInt(Opt->FindByName("FormStyle"))==2) this->WindowState = FormWindowState::Maximized;
			if(WfCommon::StrToInt(Opt->FindByName("FormStyle"))==1) this->WindowState = FormWindowState::Minimized;
			if(WfCommon::StrToInt(Opt->FindByName("FormStyle"))==0) {
				this->Location = Point(WfCommon::StrToInt(Opt->FindByName("FormLeft")),WfCommon::StrToInt(Opt->FindByName("FormTop")));
				this->Size = System::Drawing::Size(WfCommon::StrToInt(Opt->FindByName("FormWidth")),WfCommon::StrToInt(Opt->FindByName("FormHeight")));
			}
			this->timer2->Interval = WfCommon::StrToInt(Opt->FindByName("Waiting"));
			// Победитель
			WinnerFIO = "";
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
			if(Opt) {
				Opt->Save();		// Сохранить и удалить настройки
				delete Opt;
			}
		}
	private: System::ComponentModel::IContainer^  components;
	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>

	private: System::Windows::Forms::Button^  StartButton;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Timer^  timer2;



		// Переменные
		Options* Opt;			// Настройки
		String^ WinnerFIO;		// Победитель раунда

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->StartButton = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->timer2 = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// StartButton
			// 
			this->StartButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->StartButton->Location = System::Drawing::Point(25, 216);
			this->StartButton->Name = L"StartButton";
			this->StartButton->Size = System::Drawing::Size(250, 27);
			this->StartButton->TabIndex = 0;
			this->StartButton->Text = L"СТАРТ";
			this->StartButton->UseVisualStyleBackColor = true;
			this->StartButton->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(292, 273);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// timer2
			// 
			this->timer2->Tick += gcnew System::EventHandler(this, &Form1::timer2_Tick);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 14);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(292, 273);
			this->Controls->Add(this->StartButton);
			this->Controls->Add(this->pictureBox1);
			this->Font = (gcnew System::Drawing::Font(L"Arial", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Text = L"Lototron";
			this->Resize += gcnew System::EventHandler(this, &Form1::Form1_Resize);
			this->Move += gcnew System::EventHandler(this, &Form1::Form1_Move);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Form1_Move(System::Object^  sender, System::EventArgs^  e) {
				// Движение формы
				Opt->SetByName("FormLeft",WfCommon::IntToStr(this->Left));
				Opt->SetByName("FormTop",WfCommon::IntToStr(this->Top));
			 }
	private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) {
				// Изменение размеров формы
				Opt->SetByName("FormWidth",WfCommon::IntToStr(this->Width));
				Opt->SetByName("FormHeight",WfCommon::IntToStr(this->Height));
				// Update элементов формы

			 }
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				// Нажатие на кнопку СТАРТ
				// Получить ConnectionString
				char CurrentPath[200];
				GetCurrentDirectory(200,CurrentPath);
				String^ strConnection = gcnew String(CurrentPath);
				strConnection = "Provider=Microsoft.JET.OLEDB.4.0;Data Source="+strConnection;
				strConnection += "\\Lototron.mdb;";
//				this->Text = strConnection;
				// Установить соединение
				OleDb::OleDbConnection^ co = gcnew OleDb::OleDbConnection();
				co->ConnectionString = strConnection;
				co->Open();
				OleDb::OleDbCommand^ cm = gcnew OleDb::OleDbCommand();
				cm->Connection = co;
				// Получить общее число играющих
				int All = 0;
				//cm->CommandText = "select [names].[name] from [names]";
				cm->CommandText = "select count(*) from [names]";
				OleDb::OleDbDataReader^ dr = cm->ExecuteReader(System::Data::CommandBehavior::CloseConnection);
				while(dr->Read()) {
					All = System::Convert::ToInt32(dr[0]->ToString());
				}
				dr->Close();
				// Получить случайное число в интервале 1 - All
				srand((unsigned int)time(NULL));
				int Winner = rand()%All + 1;
				// Соединиться с базой и получить данные победителя
				co->Open();
				cm->CommandText = "select [id] from [names]";
				dr = cm->ExecuteReader(System::Data::CommandBehavior::CloseConnection);
				int WinnerId;
				while(dr->Read()) {
					WinnerId = System::Convert::ToInt32(dr[0]->ToString());
					if(WinnerId==Winner) break;
				}
				dr->Close();
				co->Open();
				cm->CommandText = "select [name],[family],[patronymic] from [names] where [id]="+System::Convert::ToString(Winner);
				dr = cm->ExecuteReader(System::Data::CommandBehavior::CloseConnection);
				while(dr->Read()) {
					WinnerFIO = dr[0]->ToString()+"\r"+dr[1]->ToString()+"\r"+dr[2]->ToString();
				}
				dr->Close();
				co->Close();
				// Очистить экран
				this->pictureBox1->Invalidate();
				// Включить задержку timer2
				this->timer2->Enabled = true;
				// Включить обновление перерисовки результата
				this->timer1->Enabled = true;
			 }
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
				// Перерисовка (т.к. DrawText затирается при перерисовке ImageBox1)
				// Если идет задержка timer2 - не рисовать
				if(this->timer2->Enabled==true) return;
				HWND hwnd=(HWND)this->pictureBox1->Handle.ToPointer(); 
				HDC dc = GetDC(hwnd);
				int FontHeight = this->Height/10;
				RECT Rect;
				Rect.top = (long)(this->pictureBox1->Height/2-FontHeight*1.5);
				Rect.left = 0;
				Rect.right = this->pictureBox1->Width;
				Rect.bottom = this->pictureBox1->Height;
				SetBkMode(dc,TRANSPARENT);
				SetTextColor(dc,RGB(0x255,0x0,0x0));
				HFONT f = CreateFont(FontHeight,0,0,0,FW_BOLD,0,0,0,DEFAULT_CHARSET,OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,"Arial");
				SelectObject(dc,f);
				LPCTSTR WFconv = (char*)(void*)Marshal::StringToHGlobalAnsi(WinnerFIO);
				DrawText(dc,WFconv,WinnerFIO->Length,&Rect,DT_CENTER);
			 }
private: System::Void timer2_Tick(System::Object^  sender, System::EventArgs^  e) {
			 // Остановить работу таймера
			 this->timer2->Enabled = false;
		 }
};
}
