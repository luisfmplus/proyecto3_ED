#pragma once

#include "ClienteSocket.h"
#include "datos.h"

namespace CppCLRWinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ textBox1;
	protected:
	private: System::Windows::Forms::Button^ btnEnviar;
	private: System::Windows::Forms::Button^ btnConSer;

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->btnEnviar = (gcnew System::Windows::Forms::Button());
			this->btnConSer = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(89, 30);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 20);
			this->textBox1->TabIndex = 0;
			// 
			// btnEnviar
			// 
			this->btnEnviar->Location = System::Drawing::Point(99, 56);
			this->btnEnviar->Name = L"btnEnviar";
			this->btnEnviar->Size = System::Drawing::Size(75, 23);
			this->btnEnviar->TabIndex = 1;
			this->btnEnviar->Text = L"Enviar";
			this->btnEnviar->UseVisualStyleBackColor = true;
			this->btnEnviar->Click += gcnew System::EventHandler(this, &Form1::btnEnviar_Click);
			// 
			// btnConSer
			// 
			this->btnConSer->Location = System::Drawing::Point(2, 1);
			this->btnConSer->Name = L"btnConSer";
			this->btnConSer->Size = System::Drawing::Size(102, 23);
			this->btnConSer->TabIndex = 2;
			this->btnConSer->Text = L"Conectar Servidor";
			this->btnConSer->UseVisualStyleBackColor = true;
			this->btnConSer->Click += gcnew System::EventHandler(this, &Form1::btnConSer_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->btnConSer);
			this->Controls->Add(this->btnEnviar);
			this->Controls->Add(this->textBox1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Form1_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void btnEnviar_Click(System::Object^ sender, System::EventArgs^ e) {
		string os = "";
		String^ s = textBox1->Text;
		using namespace Runtime::InteropServices;
		const char* chars =
			(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
		os = chars;
		Marshal::FreeHGlobal(IntPtr((void*)chars));
		enviarMensaje(setDato("","valor",os));
	}
	private: System::Void btnConSer_Click(System::Object^ sender, System::EventArgs^ e) {
		iniciarCliente();
	}
	};
}
