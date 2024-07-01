#pragma once
#include<string>
#include <msclr/marshal_cppstd.h>
#include "SearchEngine.h"
namespace DSA_Project {

    using namespace System;
    using namespace System::Windows::Forms;

    public ref class FileData : public System::Windows::Forms::Form
    {
    public:

        FileData(string data, string filepath)
        {
            InitializeComponent();
            
            showData(data, filepath);
            DirectoryData(filepath);
        }

    protected:
        ~FileData()
        {
            if (components)
            {
                delete components;
            }
        }
    private: System::Windows::Forms::RichTextBox^ richTextBox1;
    private: System::Windows::Forms::Label^ label1;
    private: System::Windows::Forms::Button^ button1;
    private: System::Windows::Forms::Label^ label2;
    private: System::Windows::Forms::Button^ button2;
    private: System::Windows::Forms::Label^ label3;
    private: System::Windows::Forms::ListBox^ listBox1;
    private: System::Windows::Forms::Label^ label4;
		   Memory* mm;
           ///DSA_Project::SearchEngine^ form; // Declare the SearchEngine form instance
    protected:

    protected:

    private:

        System::ComponentModel::Container^ components;

        void InitializeComponent(void)
        {
            this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->button1 = (gcnew System::Windows::Forms::Button());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->button2 = (gcnew System::Windows::Forms::Button());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->listBox1 = (gcnew System::Windows::Forms::ListBox());
            this->label4 = (gcnew System::Windows::Forms::Label());
            this->SuspendLayout();
            // 
            // richTextBox1
            // 
            this->richTextBox1->Location = System::Drawing::Point(65, 173);
            this->richTextBox1->Name = L"richTextBox1";
            this->richTextBox1->Size = System::Drawing::Size(707, 400);
            this->richTextBox1->TabIndex = 0;
            this->richTextBox1->Text = L"";
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label1->Location = System::Drawing::Point(197, 111);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(75, 22);
            this->label1->TabIndex = 0;
            this->label1->Text = L"Filepath";
            // 
            // button1
            // 
            this->button1->Location = System::Drawing::Point(25, 19);
            this->button1->Name = L"button1";
            this->button1->Size = System::Drawing::Size(107, 35);
            this->button1->TabIndex = 1;
            this->button1->Text = L"Back";
            this->button1->UseVisualStyleBackColor = true;
            this->button1->Click += gcnew System::EventHandler(this, &FileData::button1_Click);
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label2->Location = System::Drawing::Point(59, 108);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(139, 31);
            this->label2->TabIndex = 2;
            this->label2->Text = L"File Path : ";
            // 
            // button2
            // 
            this->button2->Location = System::Drawing::Point(1133, 593);
            this->button2->Name = L"button2";
            this->button2->Size = System::Drawing::Size(96, 32);
            this->button2->TabIndex = 3;
            this->button2->Text = L"Close";
            this->button2->UseVisualStyleBackColor = true;
            this->button2->Click += gcnew System::EventHandler(this, &FileData::button2_Click);
            // 
            // label3
            // 
            this->label3->AutoSize = true;
            this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label3->Location = System::Drawing::Point(723, 19);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(210, 47);
            this->label3->TabIndex = 4;
            this->label3->Text = L"FILE DATA";
            // 
            // listBox1
            // 
            this->listBox1->FormattingEnabled = true;
            this->listBox1->ItemHeight = 20;
            this->listBox1->Location = System::Drawing::Point(953, 173);
            this->listBox1->Name = L"listBox1";
            this->listBox1->Size = System::Drawing::Size(688, 404);
            this->listBox1->TabIndex = 5;
            this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &FileData::listBox1_SelectedIndexChanged);
            this->listBox1->DoubleClick += gcnew System::EventHandler(this, &FileData::listBox1_DoubleClick);
            // 
            // label4
            // 
            this->label4->AutoSize = true;
            this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label4->Location = System::Drawing::Point(955, 108);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(317, 37);
            this->label4->TabIndex = 6;
            this->label4->Text = L"Root Directory Graph";
            // 
            // FileData
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1677, 667);
            this->Controls->Add(this->label4);
            this->Controls->Add(this->listBox1);
            this->Controls->Add(this->label3);
            this->Controls->Add(this->button2);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->button1);
            this->Controls->Add(this->richTextBox1);
            this->Controls->Add(this->label1);
            this->Name = L"FileData";
            this->Text = L"FileData";
            this->ResumeLayout(false);
            this->PerformLayout();

        }
    public:
        void listBox1_DoubleClick(Object^ sender, EventArgs^ e) {
            if (listBox1->SelectedItem != nullptr) {
                string filepath = msclr::interop::marshal_as<std::string>(listBox1->SelectedItem->ToString());
                ifstream inputFile(filepath);
                if (!inputFile.is_open()) {
                    cerr << "Failed to open file: " << filepath << endl;
                    return;
                }

                string line;
                string str = "";
                
                while (getline(inputFile, line)) {
                    str += line + "\n";
                }

                inputFile.close();

                FileData^ fd = gcnew FileData(str, filepath);
                
                fd->ShowDialog();

            }

        }
		
        void DirectoryData(string filepath) {
            listBox1->Items->Add(gcnew String(filepath.c_str()));
			vector<string> DirectoryFiles = mm->traverseandreaddirectory(filepath);
            for (auto file : DirectoryFiles) {
                listBox1->Items->Add(gcnew String(file.c_str()));
            }
		}
        void showData(string data, string filepath) {
           this->richTextBox1->Text = gcnew String(data.c_str());
            this->label1->Text = gcnew String(filepath.c_str());
        }

    private:
        System::Void FileData_Load(System::Object^ sender, System::EventArgs^ e) {
        }

        // Handle button click event to show the SearchEngine form
        System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
            this->Hide();
        }

        // Handle button click event to close the current form
        System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
            this->Close();
        }
        private: System::Void listBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
        }
    };

}
