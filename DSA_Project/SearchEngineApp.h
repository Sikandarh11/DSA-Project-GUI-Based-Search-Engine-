#pragma once
#include <msclr/marshal_cppstd.h>
#include "Memory.h"

namespace DSA_Project {
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::IO;

    public ref class MainForm : public System::Windows::Forms::Form {
    public:
        MainForm(void) {
            InitializeComponent();
            mm = new Memory();
            try {
                mm->traverseAndReadDirectory("D:\\");
            }
            catch (exception e) {
                Console::WriteLine("File not opened");
            }
        }

    protected:
        ~MainForm() {
            if (components) {
                delete components;
            }
            delete mm;
        }

    private:
        System::ComponentModel::Container^ components;
        Memory* mm;
        void InitializeComponent(void) {
            System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
            this->SuspendLayout();
            // 
            // MainForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
            this->ClientSize = System::Drawing::Size(1197, 612);
            this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
            this->Name = L"MainForm";
            this->Text = L"Search Engine";
            this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
            this->BackgroundImageChanged += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
            this->ResumeLayout(false);

        }

      

    private:
        System::Void pictureBox5_Click(System::Object^ sender, System::EventArgs^ e) {
            // start();
        }

    private:
        System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
        }

    private:
        System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
        }
    };
}
