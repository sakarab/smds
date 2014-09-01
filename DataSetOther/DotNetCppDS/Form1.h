#pragma once


namespace DotNetCppDS
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary> 
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public __gc class frmMain : public System::Windows::Forms::Form
	{	
	public:
		frmMain(void)
		{
			InitializeComponent();
		}
  
    private:
        void do_btnRun_Click( System::Windows::Forms::ListView *lv );

	protected:
		void Dispose(Boolean disposing)
		{
			if (disposing && components)
			{
				components->Dispose();
			}
			__super::Dispose(disposing);
		}
    private: System::Windows::Forms::Button *  btnRun;
    private: System::Windows::Forms::ListView *  lvList;
    private: System::Windows::Forms::ColumnHeader *  lvchFileID;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container * components;

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
            this->btnRun = new System::Windows::Forms::Button();
            this->lvList = new System::Windows::Forms::ListView();
            this->lvchFileID = new System::Windows::Forms::ColumnHeader();
            this->SuspendLayout();
            // 
            // btnRun
            // 
            this->btnRun->Location = System::Drawing::Point(32, 16);
            this->btnRun->Name = S"btnRun";
            this->btnRun->TabIndex = 0;
            this->btnRun->Text = S"Run";
            this->btnRun->Click += new System::EventHandler(this, btnRun_Click);
            // 
            // lvList
            // 
            System::Windows::Forms::ColumnHeader* __mcTemp__1[] = new System::Windows::Forms::ColumnHeader*[1];
            __mcTemp__1[0] = this->lvchFileID;
            this->lvList->Columns->AddRange(__mcTemp__1);
            this->lvList->HideSelection = false;
            this->lvList->Location = System::Drawing::Point(16, 56);
            this->lvList->Name = S"lvList";
            this->lvList->Size = System::Drawing::Size(656, 408);
            this->lvList->TabIndex = 1;
            this->lvList->View = System::Windows::Forms::View::Details;
            // 
            // lvchFileID
            // 
            this->lvchFileID->Text = S"FileID";
            // 
            // frmMain
            // 
            this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
            this->ClientSize = System::Drawing::Size(712, 501);
            this->Controls->Add(this->lvList);
            this->Controls->Add(this->btnRun);
            this->Name = S"frmMain";
            this->Text = S"Form1";
            this->ResumeLayout(false);

        }	
    private: System::Void btnRun_Click(System::Object *  sender, System::EventArgs *  e)
             {
                 do_btnRun_Click( lvList );
             }

    };
}


