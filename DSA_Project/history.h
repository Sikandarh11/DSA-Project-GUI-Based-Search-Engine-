#pragma once
#include <string>
#include <msclr/marshal_cppstd.h>
#include "SearchEngine.h"
#include "FileData.h"
#include <fstream>
namespace DSA_Project {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace std;

    public ref class history : public System::Windows::Forms::Form {
    public:
        history(unordered_map<string, priority_queue<node*, vector<node*>, NodeComparator>> historyData) {
            InitializeComponent();
            callHistoryPage(historyData);
        }

        void callHistoryPage(unordered_map<string, priority_queue<node*, vector<node*>, NodeComparator>> historyData) {
            listBox1->Items->Clear();
            listBox2->Items->Clear();
            int i = 1;
            for (auto& n : historyData) {
                string str = "=========== Query " + to_string(i) + " =================";
                String^ queries = gcnew String(str.c_str());
                listBox1->Items->Add(queries);

                String^ resultItem = gcnew String(n.first.c_str());
                listBox1->Items->Add(resultItem);

                string str1 = "=========== Result of Query " + to_string(i) + " =================";
                String^ queryResult = gcnew String(str1.c_str());
                listBox2->Items->Add(queryResult);
                auto queue = n.second; // Copy the queue to iterate
                while (!queue.empty()) {
                    String^ filePath = gcnew String(queue.top()->filename.c_str());
                    listBox2->Items->Add(filePath);
                    queue.pop();
                }
                i++;
            }
        }

       

    protected:
        ~history() {
            if (components) {
                delete components;
            }
        }

        void listBox2_DoubleClick(Object^ sender, EventArgs^ e) {
            if (listBox2->SelectedItem != nullptr) {
                try {
                    string filepath = msclr::interop::marshal_as<std::string>(listBox2->SelectedItem->ToString());

                   
                    ifstream inputFile(filepath);
                    if (!inputFile.is_open()) {
                        MessageBox::Show("Failed to open file: " + gcnew String(filepath.c_str()), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
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
                catch (Exception^ ex) {
                    MessageBox::Show("An error occurred: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
            }
            else {
                MessageBox::Show("No item selected", "Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            }
        }


    private:
        System::Windows::Forms::Label^ label1;
        System::Windows::Forms::Button^ button1;
        System::Windows::Forms::Label^ label2;
        System::Windows::Forms::Button^ button2;
        System::Windows::Forms::ListBox^ listBox1;
        System::Windows::Forms::ListBox^ listBox2;
        System::Windows::Forms::Label^ label3;
        System::Windows::Forms::Label^ label4;


        System::ComponentModel::Container^ components;

        void InitializeComponent(void) {
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->button1 = (gcnew System::Windows::Forms::Button());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->button2 = (gcnew System::Windows::Forms::Button());
            this->listBox1 = (gcnew System::Windows::Forms::ListBox());
            this->listBox2 = (gcnew System::Windows::Forms::ListBox());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->label4 = (gcnew System::Windows::Forms::Label());
            this->SuspendLayout();
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label1->Location = System::Drawing::Point(203, 70);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(0, 29);
            this->label1->TabIndex = 0;
            // 
            // button1
            // 
            this->button1->Location = System::Drawing::Point(47, 18);
            this->button1->Name = L"button1";
            this->button1->Size = System::Drawing::Size(96, 37);
            this->button1->TabIndex = 1;
            this->button1->Text = L"Back";
            this->button1->UseVisualStyleBackColor = true;
            this->button1->Click += gcnew System::EventHandler(this, &history::button1_Click);
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label2->Location = System::Drawing::Point(299, 18);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(221, 37);
            this->label2->TabIndex = 2;
            this->label2->Text = L"Search History";
            // 
            // button2
            // 
            this->button2->Location = System::Drawing::Point(640, 515);
            this->button2->Name = L"button2";
            this->button2->Size = System::Drawing::Size(96, 32);
            this->button2->TabIndex = 3;
            this->button2->Text = L"Close";
            this->button2->UseVisualStyleBackColor = true;
            this->button2->Click += gcnew System::EventHandler(this, &history::button2_Click);
            // 
            // listBox1
            // 
            this->listBox1->FormattingEnabled = true;
            this->listBox1->ItemHeight = 20;
            this->listBox1->Location = System::Drawing::Point(47, 189);
            this->listBox1->Name = L"listBox1";
            this->listBox1->Size = System::Drawing::Size(289, 264);
            this->listBox1->TabIndex = 4;
            // 
            // listBox2
            // 
            this->listBox2->FormattingEnabled = true;
            this->listBox2->ItemHeight = 20;
            this->listBox2->Location = System::Drawing::Point(370, 189);
            this->listBox2->Name = L"listBox2";
            this->listBox2->Size = System::Drawing::Size(366, 264);
            this->listBox2->TabIndex = 5;
            this->listBox2->DoubleClick += gcnew System::EventHandler(this, &history::listBox2_DoubleClick);
            // 
            // label3
            // 
            this->label3->AutoSize = true;
            this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label3->Location = System::Drawing::Point(47, 119);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(107, 31);
            this->label3->TabIndex = 6;
            this->label3->Text = L"Queries";
            // 
            // label4
            // 
            this->label4->AutoSize = true;
            this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label4->Location = System::Drawing::Point(364, 119);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(130, 31);
            this->label4->TabIndex = 7;
            this->label4->Text = L"File Paths";
            // 
            // history
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(800, 570);
            this->Controls->Add(this->label4);
            this->Controls->Add(this->label3);
            this->Controls->Add(this->listBox2);
            this->Controls->Add(this->listBox1);
            this->Controls->Add(this->button2);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->button1);
            this->Controls->Add(this->label1);
            this->Name = L"history";
            this->Text = L"FileData";
            this->ResumeLayout(false);
            this->PerformLayout();

        }

    private:
        System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
            this->Hide();
        }

        System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
            this->Close();
        }

        System::Void listBox2_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
        }

        
    };
}

