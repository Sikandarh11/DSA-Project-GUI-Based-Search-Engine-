#pragma once
#include <msclr/marshal_cppstd.h>
#include "Memory.h"
#include "FileData.h"
#include "history.h"
namespace DSA_Project {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    /// Summary for SearchEngine
    /// </summary>
    using namespace System::Data;
    using namespace System::Drawing;

    /// <summary>
    public ref class SearchEngine : public System::Windows::Forms::Form
    {
    public:

        SearchEngine(void) {
            InitializeComponent();
            mm = new Memory();


            try {
               mm->readfiles(mm->traverseandreaddirectory("D:\\all"));
            }
            catch (exception e) {
                Console::WriteLine("File not opened");
            }
            SetBackgroundImage(); // Call the function to set the background image
        }
		SearchEngine(string s) {
			InitializeComponent();
			
			SetBackgroundImage(); // Call the function to set the background image
		}

    protected:
        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        ~SearchEngine()
        {
            if (components)
            {
                delete components;
            }
        }
    private: System::Windows::Forms::TextBox^ textBox1;
    private: System::Windows::Forms::Button^ button1;
    private: System::Windows::Forms::Button^ button2;
    private: System::Windows::Forms::ListBox^ listBox1;
           Memory* mm;
           
    private: System::Windows::Forms::Label^ label1;
    private: System::Windows::Forms::Label^ label2;
    protected:

    private:

        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        void InitializeComponent(void)
        {
            this->textBox1 = (gcnew System::Windows::Forms::TextBox());
            this->button1 = (gcnew System::Windows::Forms::Button());
            this->button2 = (gcnew System::Windows::Forms::Button());
            this->listBox1 = (gcnew System::Windows::Forms::ListBox());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->SuspendLayout();
            // 
            // textBox1
            // 
            this->textBox1->Location = System::Drawing::Point(242, 292);
            this->textBox1->Name = L"textBox1";
            this->textBox1->Size = System::Drawing::Size(552, 26);
            this->textBox1->TabIndex = 0;
            // 
            // button1
            // 
            this->button1->Location = System::Drawing::Point(815, 285);
            this->button1->Name = L"button1";
            this->button1->Size = System::Drawing::Size(93, 42);
            this->button1->TabIndex = 1;
            this->button1->Text = L"Search";
            this->button1->UseVisualStyleBackColor = true;
            this->button1->Click += gcnew System::EventHandler(this, &SearchEngine::button1_Click);
            // 
            // button2
            // 
            this->button2->Location = System::Drawing::Point(895, 31);
            this->button2->Name = L"button2";
            this->button2->Size = System::Drawing::Size(103, 42);
            this->button2->TabIndex = 2;
            this->button2->Text = L"History";
            this->button2->UseVisualStyleBackColor = true;
            this->button2->Click += gcnew System::EventHandler(this, &SearchEngine::button2_Click);
            // 
            // listBox1
            // 
            this->listBox1->FormattingEnabled = true;
            this->listBox1->ItemHeight = 20;
            this->listBox1->Location = System::Drawing::Point(1, 339);
            this->listBox1->Name = L"listBox1";
            this->listBox1->Size = System::Drawing::Size(1041, 224);
            this->listBox1->TabIndex = 3;
            this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &SearchEngine::listBox1_SelectedIndexChanged);
            this->listBox1->DoubleClick += gcnew System::EventHandler(this, &SearchEngine::listBox1_DoubleClick);
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->BackColor = System::Drawing::SystemColors::ButtonHighlight;
            this->label1->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 10, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label1->Location = System::Drawing::Point(23, 57);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(209, 48);
            this->label1->TabIndex = 4;
            this->label1->Text = L"Sikandar Hussain #405410\r\nSyed Adnan Aijaz #432028";
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->BackColor = System::Drawing::SystemColors::ButtonHighlight;
            this->label2->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 26, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
                System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
            this->label2->Location = System::Drawing::Point(405, 57);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(306, 63);
            this->label2->TabIndex = 5;
            this->label2->Text = L"NUST CEME";
            // 
            // SearchEngine
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1040, 557);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->listBox1);
            this->Controls->Add(this->button2);
            this->Controls->Add(this->button1);
            this->Controls->Add(this->textBox1);
            this->Name = L"SearchEngine";
            this->Text = L"SearchEngine";
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion
        // Event handler for list box double click
        void showFileData(string filepath, string str) {
            
            FileData^ fd = gcnew FileData(str, "filepath");
            fd->ShowDialog();
        }
        void listBox1_DoubleClick(Object^ sender, EventArgs^ e) {
            String^ selectedItem = listBox1->SelectedItem->ToString();

            string filepath = msclr::interop::marshal_as<std::string>(selectedItem);
            string line;
            string str = "";
			ifstream inputfile(filepath);
            while (getline(inputfile, line)) {
				str += line;
            }
            inputfile.close();
            string filepaths = mm->DirectoryPaths(filepath);

          //cout << filepath;
          FileData^ fd = gcnew FileData(str,  filepaths);
            fd->ShowDialog();
          //  showFileData(filepath, str);
        }



        
        void callHistoryForm() {
           
            try {
                history^ fd1 = gcnew history(mm->get_history());
                fd1->ShowDialog();
            }
			catch (exception e) {
				Console::WriteLine("File not opened");
			}
            

        }
        void start() {
            
            String^ search = textBox1->Text;
            priority_queue<node*, vector<node*>, NodeComparator> results = mm->search(msclr::interop::marshal_as<std::string>(search));

            listBox1->Items->Clear();
            priority_queue<node*, vector<node*>, NodeComparator> temp;
            while (!results.empty()) {
                temp.push(results.top());
                String^ resultItem = gcnew String((results.top())->filename.c_str());

                // Add the result to the ListBox
                listBox1->Items->Add(resultItem);
                results.pop();

            }


            if (listBox1->Items->Count == 0) {
                listBox1->Items->Add("No results found.");
            }
        }
    private:
        void SetBackgroundImage()
        {
            try
            {
                String^ imagePath = "D:\\bf.jpg";
                if (System::IO::File::Exists(imagePath)) // Check if the file exists
                {
                    this->BackgroundImage = Image::FromFile(imagePath);
                    this->BackgroundImageLayout = ImageLayout::Stretch; // Adjust the layout as needed
                }
                else
                {
                    MessageBox::Show("Image file not found: " + imagePath, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
            }
            catch (Exception^ ex)
            {
                MessageBox::Show("Error loading background image: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

    private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
        start();

    }
    private: System::Void listBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
    }

    private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
        callHistoryForm();

    }
    };
}