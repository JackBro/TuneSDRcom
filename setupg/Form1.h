/*
 * $Id: Form1.h,v 1.8 2012/01/31 08:38:09 vfrolov Exp $
 *
 * Copyright (c) 2007-2012 Vyacheslav Frolov
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *
 * $Log: Form1.h,v $
 * Revision 1.8  2012/01/31 08:38:09  vfrolov
 * Use node name COM<n> instead COM#
 *
 * Revision 1.7  2012/01/31 05:34:34  vfrolov
 * Added "use Ports class" option
 * Added waiting install completion
 *
 * Revision 1.6  2010/05/27 11:16:46  vfrolov
 * Added ability to put the port to the Ports class
 *
 * Revision 1.5  2009/01/12 13:04:07  vfrolov
 * Added red painting InUse portnames
 *
 * Revision 1.4  2008/05/04 09:56:47  vfrolov
 * Implemented HiddenMode option
 *
 * Revision 1.3  2008/04/08 06:52:12  vfrolov
 * Added pin OUT2
 *
 * Revision 1.2  2007/11/20 12:29:40  vfrolov
 * Fixed appearance for Vista
 *
 * Revision 1.1  2007/10/31 10:16:55  vfrolov
 * Initial revision
 *
 */

#pragma once

namespace SetupApp {

    using namespace System::Collections::Generic;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

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
			RC_isConnected=false;
			PSDR_isConnected=false;
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
		}

#pragma region Form components init
    private: System::Windows::Forms::TextBox^  PortNameB;
    private: System::Windows::Forms::TextBox^  PortNameA;
    private: System::Windows::Forms::PictureBox^  picturePinMap;
    private: System::Windows::Forms::ToolTip^  toolTip1;
    private: System::ComponentModel::IContainer^  components;
    private: System::Windows::Forms::Button^  buttonRemovePair;
    private: System::Windows::Forms::Button^  buttonAddPair;
    private: System::Windows::Forms::Button^  buttonApply;
    private: System::Windows::Forms::Button^  buttonReset;
    private: System::Windows::Forms::CheckBox^  EmuBrB;
    private: System::Windows::Forms::CheckBox^  EmuOverrunB;
    private: System::Windows::Forms::CheckBox^  PlugInModeB;
    private: System::Windows::Forms::CheckBox^  ExclusiveModeB;
    private: System::Windows::Forms::CheckBox^  ExclusiveModeA;
    private: System::Windows::Forms::CheckBox^  PlugInModeA;
    private: System::Windows::Forms::CheckBox^  EmuOverrunA;
    private: System::Windows::Forms::CheckBox^  EmuBrA;
    private: System::Windows::Forms::CheckBox^  HiddenModeA;
    private: System::Windows::Forms::CheckBox^  HiddenModeB;
    private: System::Windows::Forms::Label^  pinNameON;
    private: System::Windows::Forms::Label^  pinNameA_RX;
    private: System::Windows::Forms::Label^  pinNameA_DTR;
    private: System::Windows::Forms::Label^  pinNameA_TX;
    private: System::Windows::Forms::Label^  pinNameA_DSR;
    private: System::Windows::Forms::Label^  pinNameA_DCD;
    private: System::Windows::Forms::Label^  pinNameA_RTS;
    private: System::Windows::Forms::Label^  pinNameA_CTS;
    private: System::Windows::Forms::Label^  pinNameA_RI;
    private: System::Windows::Forms::Label^  pinNameA_OUT1;
    private: System::Windows::Forms::Label^  pinNameA_OUT2;
    private: System::Windows::Forms::Label^  pinNameA_OPEN;
    private: System::Windows::Forms::Label^  pinNameB_OPEN;
    private: System::Windows::Forms::Label^  pinNameB_OUT1;
    private: System::Windows::Forms::Label^  pinNameB_OUT2;
    private: System::Windows::Forms::Label^  pinNameB_RI;
    private: System::Windows::Forms::Label^  pinNameB_CTS;
    private: System::Windows::Forms::Label^  pinNameB_RTS;
    private: System::Windows::Forms::Label^  pinNameB_DCD;
    private: System::Windows::Forms::Label^  pinNameB_DSR;
    private: System::Windows::Forms::Label^  pinNameB_TX;
    private: System::Windows::Forms::Label^  pinNameB_DTR;
    private: System::Windows::Forms::Label^  pinNameB_RX;
    private: System::Windows::Forms::CheckBox^  UsePortsClassB;
    private: System::Windows::Forms::CheckBox^  UsePortsClassA;




	private: System::Windows::Forms::Panel^  panel1;

	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::IO::Ports::SerialPort^  serialRC;
	private: System::IO::Ports::SerialPort^  serialPSDR;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::CheckBox^  checkBoxPSDR;
	private: System::Windows::Forms::CheckBox^  checkBoxRC;
	private: System::Windows::Forms::Timer^  timerOpenPorts;
	private: System::Windows::Forms::Timer^  timerReadRC;
	private: System::Windows::Forms::NotifyIcon^  notifyIcon;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  buttonConnect;

	private: System::Windows::Forms::TreeView^  pairList;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
#pragma endregion

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->PortNameB = (gcnew System::Windows::Forms::TextBox());
			this->PortNameA = (gcnew System::Windows::Forms::TextBox());
			this->UsePortsClassB = (gcnew System::Windows::Forms::CheckBox());
			this->UsePortsClassA = (gcnew System::Windows::Forms::CheckBox());
			this->pinNameON = (gcnew System::Windows::Forms::Label());
			this->picturePinMap = (gcnew System::Windows::Forms::PictureBox());
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->EmuBrB = (gcnew System::Windows::Forms::CheckBox());
			this->EmuOverrunB = (gcnew System::Windows::Forms::CheckBox());
			this->PlugInModeB = (gcnew System::Windows::Forms::CheckBox());
			this->ExclusiveModeB = (gcnew System::Windows::Forms::CheckBox());
			this->ExclusiveModeA = (gcnew System::Windows::Forms::CheckBox());
			this->PlugInModeA = (gcnew System::Windows::Forms::CheckBox());
			this->EmuOverrunA = (gcnew System::Windows::Forms::CheckBox());
			this->EmuBrA = (gcnew System::Windows::Forms::CheckBox());
			this->HiddenModeA = (gcnew System::Windows::Forms::CheckBox());
			this->HiddenModeB = (gcnew System::Windows::Forms::CheckBox());
			this->pinNameA_RX = (gcnew System::Windows::Forms::Label());
			this->pinNameA_DTR = (gcnew System::Windows::Forms::Label());
			this->pinNameA_TX = (gcnew System::Windows::Forms::Label());
			this->pinNameA_DSR = (gcnew System::Windows::Forms::Label());
			this->pinNameA_DCD = (gcnew System::Windows::Forms::Label());
			this->pinNameA_RTS = (gcnew System::Windows::Forms::Label());
			this->pinNameA_CTS = (gcnew System::Windows::Forms::Label());
			this->pinNameA_RI = (gcnew System::Windows::Forms::Label());
			this->pinNameA_OUT1 = (gcnew System::Windows::Forms::Label());
			this->pinNameA_OUT2 = (gcnew System::Windows::Forms::Label());
			this->pinNameA_OPEN = (gcnew System::Windows::Forms::Label());
			this->pinNameB_OPEN = (gcnew System::Windows::Forms::Label());
			this->pinNameB_OUT1 = (gcnew System::Windows::Forms::Label());
			this->pinNameB_OUT2 = (gcnew System::Windows::Forms::Label());
			this->pinNameB_RI = (gcnew System::Windows::Forms::Label());
			this->pinNameB_CTS = (gcnew System::Windows::Forms::Label());
			this->pinNameB_RTS = (gcnew System::Windows::Forms::Label());
			this->pinNameB_DCD = (gcnew System::Windows::Forms::Label());
			this->pinNameB_DSR = (gcnew System::Windows::Forms::Label());
			this->pinNameB_TX = (gcnew System::Windows::Forms::Label());
			this->pinNameB_DTR = (gcnew System::Windows::Forms::Label());
			this->pinNameB_RX = (gcnew System::Windows::Forms::Label());
			this->pairList = (gcnew System::Windows::Forms::TreeView());
			this->buttonRemovePair = (gcnew System::Windows::Forms::Button());
			this->buttonAddPair = (gcnew System::Windows::Forms::Button());
			this->buttonApply = (gcnew System::Windows::Forms::Button());
			this->buttonReset = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->buttonConnect = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->checkBoxPSDR = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxRC = (gcnew System::Windows::Forms::CheckBox());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->serialRC = (gcnew System::IO::Ports::SerialPort(this->components));
			this->serialPSDR = (gcnew System::IO::Ports::SerialPort(this->components));
			this->timerOpenPorts = (gcnew System::Windows::Forms::Timer(this->components));
			this->timerReadRC = (gcnew System::Windows::Forms::Timer(this->components));
			this->notifyIcon = (gcnew System::Windows::Forms::NotifyIcon(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picturePinMap))->BeginInit();
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// PortNameB
			// 
			resources->ApplyResources(this->PortNameB, L"PortNameB");
			this->PortNameB->Name = L"PortNameB";
			this->toolTip1->SetToolTip(this->PortNameB, resources->GetString(L"PortNameB.ToolTip"));
			this->PortNameB->TextChanged += gcnew System::EventHandler(this, &Form1::PortNameB_Changed);
			// 
			// PortNameA
			// 
			resources->ApplyResources(this->PortNameA, L"PortNameA");
			this->PortNameA->Name = L"PortNameA";
			this->toolTip1->SetToolTip(this->PortNameA, resources->GetString(L"PortNameA.ToolTip"));
			this->PortNameA->TextChanged += gcnew System::EventHandler(this, &Form1::PortNameA_Changed);
			// 
			// UsePortsClassB
			// 
			resources->ApplyResources(this->UsePortsClassB, L"UsePortsClassB");
			this->UsePortsClassB->Name = L"UsePortsClassB";
			this->toolTip1->SetToolTip(this->UsePortsClassB, resources->GetString(L"UsePortsClassB.ToolTip"));
			this->UsePortsClassB->UseVisualStyleBackColor = true;
			this->UsePortsClassB->CheckedChanged += gcnew System::EventHandler(this, &Form1::UsePortsClassB_Changed);
			// 
			// UsePortsClassA
			// 
			resources->ApplyResources(this->UsePortsClassA, L"UsePortsClassA");
			this->UsePortsClassA->Name = L"UsePortsClassA";
			this->toolTip1->SetToolTip(this->UsePortsClassA, resources->GetString(L"UsePortsClassA.ToolTip"));
			this->UsePortsClassA->UseVisualStyleBackColor = true;
			this->UsePortsClassA->CheckedChanged += gcnew System::EventHandler(this, &Form1::UsePortsClassA_Changed);
			// 
			// pinNameON
			// 
			resources->ApplyResources(this->pinNameON, L"pinNameON");
			this->pinNameON->Name = L"pinNameON";
			this->toolTip1->SetToolTip(this->pinNameON, resources->GetString(L"pinNameON.ToolTip"));
			// 
			// picturePinMap
			// 
			this->picturePinMap->BackColor = System::Drawing::SystemColors::Control;
			this->picturePinMap->Cursor = System::Windows::Forms::Cursors::Hand;
			resources->ApplyResources(this->picturePinMap, L"picturePinMap");
			this->picturePinMap->Name = L"picturePinMap";
			this->picturePinMap->TabStop = false;
			this->toolTip1->SetToolTip(this->picturePinMap, resources->GetString(L"picturePinMap.ToolTip"));
			this->picturePinMap->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::picturePinMap_Paint);
			this->picturePinMap->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::picturePinMap_MouseDoubleClick);
			this->picturePinMap->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::picturePinMap_MouseDown);
			this->picturePinMap->MouseLeave += gcnew System::EventHandler(this, &Form1::picturePinMap_MouseLeave);
			this->picturePinMap->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::picturePinMap_MouseMove);
			this->picturePinMap->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::picturePinMap_MouseUp);
			// 
			// EmuBrB
			// 
			resources->ApplyResources(this->EmuBrB, L"EmuBrB");
			this->EmuBrB->Name = L"EmuBrB";
			this->toolTip1->SetToolTip(this->EmuBrB, resources->GetString(L"EmuBrB.ToolTip"));
			this->EmuBrB->UseVisualStyleBackColor = true;
			this->EmuBrB->CheckedChanged += gcnew System::EventHandler(this, &Form1::EmuBrB_Changed);
			// 
			// EmuOverrunB
			// 
			resources->ApplyResources(this->EmuOverrunB, L"EmuOverrunB");
			this->EmuOverrunB->Name = L"EmuOverrunB";
			this->toolTip1->SetToolTip(this->EmuOverrunB, resources->GetString(L"EmuOverrunB.ToolTip"));
			this->EmuOverrunB->UseVisualStyleBackColor = true;
			this->EmuOverrunB->CheckedChanged += gcnew System::EventHandler(this, &Form1::EmuOverrunB_Changed);
			// 
			// PlugInModeB
			// 
			resources->ApplyResources(this->PlugInModeB, L"PlugInModeB");
			this->PlugInModeB->Name = L"PlugInModeB";
			this->toolTip1->SetToolTip(this->PlugInModeB, resources->GetString(L"PlugInModeB.ToolTip"));
			this->PlugInModeB->UseVisualStyleBackColor = true;
			this->PlugInModeB->CheckedChanged += gcnew System::EventHandler(this, &Form1::PlugInModeB_Changed);
			// 
			// ExclusiveModeB
			// 
			resources->ApplyResources(this->ExclusiveModeB, L"ExclusiveModeB");
			this->ExclusiveModeB->Name = L"ExclusiveModeB";
			this->toolTip1->SetToolTip(this->ExclusiveModeB, resources->GetString(L"ExclusiveModeB.ToolTip"));
			this->ExclusiveModeB->UseVisualStyleBackColor = true;
			this->ExclusiveModeB->CheckedChanged += gcnew System::EventHandler(this, &Form1::ExclusiveModeB_Changed);
			// 
			// ExclusiveModeA
			// 
			resources->ApplyResources(this->ExclusiveModeA, L"ExclusiveModeA");
			this->ExclusiveModeA->Name = L"ExclusiveModeA";
			this->toolTip1->SetToolTip(this->ExclusiveModeA, resources->GetString(L"ExclusiveModeA.ToolTip"));
			this->ExclusiveModeA->UseVisualStyleBackColor = true;
			this->ExclusiveModeA->CheckedChanged += gcnew System::EventHandler(this, &Form1::ExclusiveModeA_Changed);
			// 
			// PlugInModeA
			// 
			resources->ApplyResources(this->PlugInModeA, L"PlugInModeA");
			this->PlugInModeA->Name = L"PlugInModeA";
			this->toolTip1->SetToolTip(this->PlugInModeA, resources->GetString(L"PlugInModeA.ToolTip"));
			this->PlugInModeA->UseVisualStyleBackColor = true;
			this->PlugInModeA->CheckedChanged += gcnew System::EventHandler(this, &Form1::PlugInModeA_Changed);
			// 
			// EmuOverrunA
			// 
			resources->ApplyResources(this->EmuOverrunA, L"EmuOverrunA");
			this->EmuOverrunA->Name = L"EmuOverrunA";
			this->toolTip1->SetToolTip(this->EmuOverrunA, resources->GetString(L"EmuOverrunA.ToolTip"));
			this->EmuOverrunA->UseVisualStyleBackColor = true;
			this->EmuOverrunA->CheckedChanged += gcnew System::EventHandler(this, &Form1::EmuOverrunA_Changed);
			// 
			// EmuBrA
			// 
			resources->ApplyResources(this->EmuBrA, L"EmuBrA");
			this->EmuBrA->Name = L"EmuBrA";
			this->toolTip1->SetToolTip(this->EmuBrA, resources->GetString(L"EmuBrA.ToolTip"));
			this->EmuBrA->UseVisualStyleBackColor = true;
			this->EmuBrA->CheckedChanged += gcnew System::EventHandler(this, &Form1::EmuBrA_Changed);
			// 
			// HiddenModeA
			// 
			resources->ApplyResources(this->HiddenModeA, L"HiddenModeA");
			this->HiddenModeA->Name = L"HiddenModeA";
			this->toolTip1->SetToolTip(this->HiddenModeA, resources->GetString(L"HiddenModeA.ToolTip"));
			this->HiddenModeA->UseVisualStyleBackColor = true;
			this->HiddenModeA->CheckedChanged += gcnew System::EventHandler(this, &Form1::HiddenModeA_Changed);
			// 
			// HiddenModeB
			// 
			resources->ApplyResources(this->HiddenModeB, L"HiddenModeB");
			this->HiddenModeB->Name = L"HiddenModeB";
			this->toolTip1->SetToolTip(this->HiddenModeB, resources->GetString(L"HiddenModeB.ToolTip"));
			this->HiddenModeB->UseVisualStyleBackColor = true;
			this->HiddenModeB->CheckedChanged += gcnew System::EventHandler(this, &Form1::HiddenModeB_Changed);
			// 
			// pinNameA_RX
			// 
			resources->ApplyResources(this->pinNameA_RX, L"pinNameA_RX");
			this->pinNameA_RX->Name = L"pinNameA_RX";
			this->toolTip1->SetToolTip(this->pinNameA_RX, resources->GetString(L"pinNameA_RX.ToolTip"));
			// 
			// pinNameA_DTR
			// 
			resources->ApplyResources(this->pinNameA_DTR, L"pinNameA_DTR");
			this->pinNameA_DTR->Name = L"pinNameA_DTR";
			this->toolTip1->SetToolTip(this->pinNameA_DTR, resources->GetString(L"pinNameA_DTR.ToolTip"));
			// 
			// pinNameA_TX
			// 
			resources->ApplyResources(this->pinNameA_TX, L"pinNameA_TX");
			this->pinNameA_TX->Name = L"pinNameA_TX";
			this->toolTip1->SetToolTip(this->pinNameA_TX, resources->GetString(L"pinNameA_TX.ToolTip"));
			// 
			// pinNameA_DSR
			// 
			resources->ApplyResources(this->pinNameA_DSR, L"pinNameA_DSR");
			this->pinNameA_DSR->Name = L"pinNameA_DSR";
			this->toolTip1->SetToolTip(this->pinNameA_DSR, resources->GetString(L"pinNameA_DSR.ToolTip"));
			// 
			// pinNameA_DCD
			// 
			resources->ApplyResources(this->pinNameA_DCD, L"pinNameA_DCD");
			this->pinNameA_DCD->Name = L"pinNameA_DCD";
			this->toolTip1->SetToolTip(this->pinNameA_DCD, resources->GetString(L"pinNameA_DCD.ToolTip"));
			// 
			// pinNameA_RTS
			// 
			resources->ApplyResources(this->pinNameA_RTS, L"pinNameA_RTS");
			this->pinNameA_RTS->Name = L"pinNameA_RTS";
			this->toolTip1->SetToolTip(this->pinNameA_RTS, resources->GetString(L"pinNameA_RTS.ToolTip"));
			// 
			// pinNameA_CTS
			// 
			resources->ApplyResources(this->pinNameA_CTS, L"pinNameA_CTS");
			this->pinNameA_CTS->Name = L"pinNameA_CTS";
			this->toolTip1->SetToolTip(this->pinNameA_CTS, resources->GetString(L"pinNameA_CTS.ToolTip"));
			// 
			// pinNameA_RI
			// 
			resources->ApplyResources(this->pinNameA_RI, L"pinNameA_RI");
			this->pinNameA_RI->Name = L"pinNameA_RI";
			this->toolTip1->SetToolTip(this->pinNameA_RI, resources->GetString(L"pinNameA_RI.ToolTip"));
			// 
			// pinNameA_OUT1
			// 
			resources->ApplyResources(this->pinNameA_OUT1, L"pinNameA_OUT1");
			this->pinNameA_OUT1->Name = L"pinNameA_OUT1";
			this->toolTip1->SetToolTip(this->pinNameA_OUT1, resources->GetString(L"pinNameA_OUT1.ToolTip"));
			// 
			// pinNameA_OUT2
			// 
			resources->ApplyResources(this->pinNameA_OUT2, L"pinNameA_OUT2");
			this->pinNameA_OUT2->Name = L"pinNameA_OUT2";
			this->toolTip1->SetToolTip(this->pinNameA_OUT2, resources->GetString(L"pinNameA_OUT2.ToolTip"));
			// 
			// pinNameA_OPEN
			// 
			resources->ApplyResources(this->pinNameA_OPEN, L"pinNameA_OPEN");
			this->pinNameA_OPEN->Name = L"pinNameA_OPEN";
			this->toolTip1->SetToolTip(this->pinNameA_OPEN, resources->GetString(L"pinNameA_OPEN.ToolTip"));
			// 
			// pinNameB_OPEN
			// 
			resources->ApplyResources(this->pinNameB_OPEN, L"pinNameB_OPEN");
			this->pinNameB_OPEN->Name = L"pinNameB_OPEN";
			this->toolTip1->SetToolTip(this->pinNameB_OPEN, resources->GetString(L"pinNameB_OPEN.ToolTip"));
			// 
			// pinNameB_OUT1
			// 
			resources->ApplyResources(this->pinNameB_OUT1, L"pinNameB_OUT1");
			this->pinNameB_OUT1->Name = L"pinNameB_OUT1";
			this->toolTip1->SetToolTip(this->pinNameB_OUT1, resources->GetString(L"pinNameB_OUT1.ToolTip"));
			// 
			// pinNameB_OUT2
			// 
			resources->ApplyResources(this->pinNameB_OUT2, L"pinNameB_OUT2");
			this->pinNameB_OUT2->Name = L"pinNameB_OUT2";
			this->toolTip1->SetToolTip(this->pinNameB_OUT2, resources->GetString(L"pinNameB_OUT2.ToolTip"));
			// 
			// pinNameB_RI
			// 
			resources->ApplyResources(this->pinNameB_RI, L"pinNameB_RI");
			this->pinNameB_RI->Name = L"pinNameB_RI";
			this->toolTip1->SetToolTip(this->pinNameB_RI, resources->GetString(L"pinNameB_RI.ToolTip"));
			// 
			// pinNameB_CTS
			// 
			resources->ApplyResources(this->pinNameB_CTS, L"pinNameB_CTS");
			this->pinNameB_CTS->Name = L"pinNameB_CTS";
			this->toolTip1->SetToolTip(this->pinNameB_CTS, resources->GetString(L"pinNameB_CTS.ToolTip"));
			// 
			// pinNameB_RTS
			// 
			resources->ApplyResources(this->pinNameB_RTS, L"pinNameB_RTS");
			this->pinNameB_RTS->Name = L"pinNameB_RTS";
			this->toolTip1->SetToolTip(this->pinNameB_RTS, resources->GetString(L"pinNameB_RTS.ToolTip"));
			// 
			// pinNameB_DCD
			// 
			resources->ApplyResources(this->pinNameB_DCD, L"pinNameB_DCD");
			this->pinNameB_DCD->Name = L"pinNameB_DCD";
			this->toolTip1->SetToolTip(this->pinNameB_DCD, resources->GetString(L"pinNameB_DCD.ToolTip"));
			// 
			// pinNameB_DSR
			// 
			resources->ApplyResources(this->pinNameB_DSR, L"pinNameB_DSR");
			this->pinNameB_DSR->Name = L"pinNameB_DSR";
			this->toolTip1->SetToolTip(this->pinNameB_DSR, resources->GetString(L"pinNameB_DSR.ToolTip"));
			// 
			// pinNameB_TX
			// 
			resources->ApplyResources(this->pinNameB_TX, L"pinNameB_TX");
			this->pinNameB_TX->Name = L"pinNameB_TX";
			this->toolTip1->SetToolTip(this->pinNameB_TX, resources->GetString(L"pinNameB_TX.ToolTip"));
			// 
			// pinNameB_DTR
			// 
			resources->ApplyResources(this->pinNameB_DTR, L"pinNameB_DTR");
			this->pinNameB_DTR->Name = L"pinNameB_DTR";
			this->toolTip1->SetToolTip(this->pinNameB_DTR, resources->GetString(L"pinNameB_DTR.ToolTip"));
			// 
			// pinNameB_RX
			// 
			resources->ApplyResources(this->pinNameB_RX, L"pinNameB_RX");
			this->pinNameB_RX->Name = L"pinNameB_RX";
			this->toolTip1->SetToolTip(this->pinNameB_RX, resources->GetString(L"pinNameB_RX.ToolTip"));
			// 
			// pairList
			// 
			this->pairList->HideSelection = false;
			resources->ApplyResources(this->pairList, L"pairList");
			this->pairList->Name = L"pairList";
			this->toolTip1->SetToolTip(this->pairList, resources->GetString(L"pairList.ToolTip"));
			this->pairList->BeforeSelect += gcnew System::Windows::Forms::TreeViewCancelEventHandler(this, &Form1::pairsList_BeforeSelect);
			this->pairList->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &Form1::pairsList_AfterSelect);
			// 
			// buttonRemovePair
			// 
			resources->ApplyResources(this->buttonRemovePair, L"buttonRemovePair");
			this->buttonRemovePair->Name = L"buttonRemovePair";
			this->toolTip1->SetToolTip(this->buttonRemovePair, resources->GetString(L"buttonRemovePair.ToolTip"));
			this->buttonRemovePair->UseVisualStyleBackColor = true;
			this->buttonRemovePair->Click += gcnew System::EventHandler(this, &Form1::buttonRemovePair_Click);
			// 
			// buttonAddPair
			// 
			resources->ApplyResources(this->buttonAddPair, L"buttonAddPair");
			this->buttonAddPair->Name = L"buttonAddPair";
			this->toolTip1->SetToolTip(this->buttonAddPair, resources->GetString(L"buttonAddPair.ToolTip"));
			this->buttonAddPair->UseVisualStyleBackColor = true;
			this->buttonAddPair->Click += gcnew System::EventHandler(this, &Form1::buttonAddPair_Click);
			// 
			// buttonApply
			// 
			resources->ApplyResources(this->buttonApply, L"buttonApply");
			this->buttonApply->Name = L"buttonApply";
			this->toolTip1->SetToolTip(this->buttonApply, resources->GetString(L"buttonApply.ToolTip"));
			this->buttonApply->UseVisualStyleBackColor = true;
			this->buttonApply->Click += gcnew System::EventHandler(this, &Form1::buttonApply_Click);
			// 
			// buttonReset
			// 
			resources->ApplyResources(this->buttonReset, L"buttonReset");
			this->buttonReset->Name = L"buttonReset";
			this->toolTip1->SetToolTip(this->buttonReset, resources->GetString(L"buttonReset.ToolTip"));
			this->buttonReset->UseVisualStyleBackColor = true;
			this->buttonReset->Click += gcnew System::EventHandler(this, &Form1::buttonReset_Click);
			// 
			// panel1
			// 
			resources->ApplyResources(this->panel1, L"panel1");
			this->panel1->Controls->Add(this->buttonConnect);
			this->panel1->Controls->Add(this->label1);
			this->panel1->Controls->Add(this->checkBoxPSDR);
			this->panel1->Controls->Add(this->checkBoxRC);
			this->panel1->Controls->Add(this->comboBox1);
			this->panel1->Controls->Add(this->textBox1);
			this->panel1->Name = L"panel1";
			// 
			// buttonConnect
			// 
			resources->ApplyResources(this->buttonConnect, L"buttonConnect");
			this->buttonConnect->Name = L"buttonConnect";
			this->buttonConnect->UseVisualStyleBackColor = true;
			this->buttonConnect->Click += gcnew System::EventHandler(this, &Form1::buttonConnect_Click);
			// 
			// label1
			// 
			resources->ApplyResources(this->label1, L"label1");
			this->label1->Name = L"label1";
			// 
			// checkBoxPSDR
			// 
			resources->ApplyResources(this->checkBoxPSDR, L"checkBoxPSDR");
			this->checkBoxPSDR->Name = L"checkBoxPSDR";
			this->checkBoxPSDR->UseVisualStyleBackColor = true;
			// 
			// checkBoxRC
			// 
			resources->ApplyResources(this->checkBoxRC, L"checkBoxRC");
			this->checkBoxRC->Name = L"checkBoxRC";
			this->checkBoxRC->UseVisualStyleBackColor = true;
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			resources->ApplyResources(this->comboBox1, L"comboBox1");
			this->comboBox1->Name = L"comboBox1";
			// 
			// textBox1
			// 
			resources->ApplyResources(this->textBox1, L"textBox1");
			this->textBox1->Name = L"textBox1";
			// 
			// serialRC
			// 
			this->serialRC->ReadTimeout = 1;
			this->serialRC->WriteTimeout = 1;
			// 
			// serialPSDR
			// 
			this->serialPSDR->PortName = L"COM98";
			this->serialPSDR->ReadTimeout = 5;
			this->serialPSDR->WriteTimeout = 5;
			// 
			// timerOpenPorts
			// 
			this->timerOpenPorts->Enabled = true;
			this->timerOpenPorts->Interval = 3000;
			this->timerOpenPorts->Tick += gcnew System::EventHandler(this, &Form1::timerOpenPorts_Tick);
			// 
			// timerReadRC
			// 
			this->timerReadRC->Enabled = true;
			this->timerReadRC->Tick += gcnew System::EventHandler(this, &Form1::timerReadRC_Tick);
			// 
			// notifyIcon
			// 
			this->notifyIcon->BalloonTipIcon = System::Windows::Forms::ToolTipIcon::Info;
			resources->ApplyResources(this->notifyIcon, L"notifyIcon");
			this->notifyIcon->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::notifyIcon_MouseClick);
			// 
			// Form1
			// 
			resources->ApplyResources(this, L"$this");
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->UsePortsClassA);
			this->Controls->Add(this->UsePortsClassB);
			this->Controls->Add(this->HiddenModeA);
			this->Controls->Add(this->HiddenModeB);
			this->Controls->Add(this->pinNameB_OPEN);
			this->Controls->Add(this->pinNameB_OUT1);
			this->Controls->Add(this->pinNameB_OUT2);
			this->Controls->Add(this->pinNameB_RI);
			this->Controls->Add(this->pinNameB_CTS);
			this->Controls->Add(this->pinNameB_RTS);
			this->Controls->Add(this->pinNameB_DCD);
			this->Controls->Add(this->pinNameB_DSR);
			this->Controls->Add(this->pinNameB_TX);
			this->Controls->Add(this->pinNameB_DTR);
			this->Controls->Add(this->pinNameB_RX);
			this->Controls->Add(this->pinNameA_OPEN);
			this->Controls->Add(this->pinNameA_OUT1);
			this->Controls->Add(this->pinNameA_OUT2);
			this->Controls->Add(this->pinNameA_RI);
			this->Controls->Add(this->pinNameA_CTS);
			this->Controls->Add(this->pinNameA_RTS);
			this->Controls->Add(this->pinNameA_DCD);
			this->Controls->Add(this->pinNameA_DSR);
			this->Controls->Add(this->pinNameA_TX);
			this->Controls->Add(this->pinNameA_DTR);
			this->Controls->Add(this->pinNameA_RX);
			this->Controls->Add(this->ExclusiveModeA);
			this->Controls->Add(this->PlugInModeA);
			this->Controls->Add(this->EmuOverrunA);
			this->Controls->Add(this->EmuBrA);
			this->Controls->Add(this->ExclusiveModeB);
			this->Controls->Add(this->PlugInModeB);
			this->Controls->Add(this->EmuOverrunB);
			this->Controls->Add(this->EmuBrB);
			this->Controls->Add(this->buttonReset);
			this->Controls->Add(this->buttonApply);
			this->Controls->Add(this->buttonAddPair);
			this->Controls->Add(this->buttonRemovePair);
			this->Controls->Add(this->pairList);
			this->Controls->Add(this->PortNameB);
			this->Controls->Add(this->PortNameA);
			this->Controls->Add(this->pinNameON);
			this->Controls->Add(this->picturePinMap);
			this->MaximizeBox = false;
			this->Name = L"Form1";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::Form1_FormClosing);
			this->Load += gcnew System::EventHandler(this, &Form1::this_Load);
			this->SizeChanged += gcnew System::EventHandler(this, &Form1::Form1_SizeChanged);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picturePinMap))->EndInit();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

#pragma region COM0COM code
    private:

        String ^GetControlValue(CheckBox ^control) {
          return control->Checked ? "YES" : "NO";
        }

        Void SetControlValue(CheckBox ^control, String ^value) {
          control->Checked = (value->ToUpper() == "YES") ? true : false;
        }

        /////////////////////////////////////////////////////////////////////
        #define DeclareControlPair(controlClass, control) \
          array<controlClass ^> ^control##_pair; \
          Void control##_Init() { \
            control##_pair = gcnew array<controlClass ^>{control##A, control##B}; \
          } \
          Void control##A_Changed(Object ^/*sender*/, EventArgs ^/*e*/) { \
            control##_Changed(0); \
          } \
          Void control##B_Changed(Object ^/*sender*/, EventArgs ^/*e*/) { \
            control##_Changed(1); \
          } \

        #define DeclareControlPairCheckBox(control) \
          DeclareControlPair(CheckBox, control) \
          Void control##_Changed(int i) { \
            try { \
              String ^key = (gcnew String(#control))->ToLower(); \
              String ^value = GetControlValue(control##_pair[i])->ToUpper(); \
              if (pairs[pairList->SelectedNode->Name][i][key] != value) { \
                control##_pair[i]->ForeColor = Color::Blue; \
                return; \
              } \
            } \
            catch (Exception^ /*e*/) { \
            } \
            control##_pair[i]->ForeColor = System::Drawing::SystemColors::ControlText; \
          } \
          Void control##_GetChanges(int i, PortPair ^portChanges) { \
            try { \
              String ^key = (gcnew String(#control))->ToLower(); \
              String ^value = GetControlValue(control##_pair[i])->ToUpper(); \
              if (pairs[pairList->SelectedNode->Name][i][key] != value) \
                portChanges[i][key] = value; \
            } \
            catch (Exception^ /*e*/) { \
            } \
          } \
          Void control##_Reset(int i) { \
            try { \
              String ^key = (gcnew String(#control))->ToLower(); \
              SetControlValue(control##_pair[i], pairs[pairList->SelectedNode->Name][i][key]); \
            } \
            catch (Exception^ /*e*/) { \
              SetControlValue(control##_pair[i], ""); \
            } \
            control##_Changed(i); \
          } \
        /////////////////////////////////////////////////////////////////////

    private:

        DeclareControlPair(TextBox, PortName)
        DeclareControlPair(CheckBox, UsePortsClass)

        Void PortName_GetCurrent(int i, String ^&name, bool &enabled, bool &checked) {
          try {
            name = pairs[pairList->SelectedNode->Name][i][(gcnew String("PortName"))->ToLower()];

            if (name->ToUpper() == "COM#") {
              checked = true;

              try {
                name = pairs[pairList->SelectedNode->Name][i][(gcnew String("RealPortName"))->ToLower()];
                enabled = true;
              }
              catch (Exception^ /*e*/) {
                name = "";
                enabled = false;
              }
            } else {
              checked = false;
              enabled = true;
            }
          }
          catch (Exception^ /*e*/) {
            checked = false;
            name = "";
            enabled = true;
          }
        }

        Void PortName_Changed(int i) {
          String ^name = gcnew String("");
          bool enabled;
          bool checked;

          PortName_GetCurrent(i, name, enabled, checked);

          String ^value = PortName_pair[i]->Text->ToUpper();

          if (name != value) {
            PortName_pair[i]->ForeColor = (pairs->IsValidName(value) ? Color::Blue : Color::Red);
          } else {
            PortName_pair[i]->ForeColor = System::Drawing::SystemColors::ControlText;
          }

          if (!checked != !UsePortsClass_pair[i]->Checked) {
            UsePortsClass_pair[i]->ForeColor = Color::Blue;
          } else {
            UsePortsClass_pair[i]->ForeColor = System::Drawing::SystemColors::ControlText;
          }

          PortName_pair[i]->Enabled = (!UsePortsClass_pair[i]->Checked || (checked && enabled));
        }

        Void PortName_GetChanges(int i, PortPair ^portChanges) {
          String ^name = gcnew String("");
          bool enabled;
          bool checked;

          PortName_GetCurrent(i, name, enabled, checked);

          String ^value = PortName_pair[i]->Text->ToUpper();

          if (UsePortsClass_pair[i]->Checked) {
            if (checked) {
              if (name != value) {
                portChanges[i][(gcnew String("RealPortName"))->ToLower()] = value;
              }
            } else {
              portChanges[i][(gcnew String("PortName"))->ToLower()] = "COM#";
            }
          } else {
            if (checked) {
              portChanges[i][(gcnew String("PortName"))->ToLower()] = value;
            } else {
              if (name != value) {
                portChanges[i][(gcnew String("PortName"))->ToLower()] = value;
              }
            }
          }
        }

        Void PortName_Reset(int i) {
          String ^name = gcnew String("");
          bool enabled;
          bool checked;

          PortName_GetCurrent(i, name, enabled, checked);

          PortName_pair[i]->Text = name;
          PortName_pair[i]->Enabled = enabled;
          UsePortsClass_pair[i]->Checked = checked;

          PortName_Changed(i);
        }

        Void UsePortsClass_Changed(int i) {
          String ^name = gcnew String("");
          bool enabled;
          bool checked;

          PortName_GetCurrent(i, name, enabled, checked);

          if (checked || !UsePortsClass_pair[i]->Checked) {
            if (!UsePortsClass_pair[i]->Checked && name == "") {
              PortName_pair[i]->Text = "-";
            } else {
              PortName_pair[i]->Text = name;
            }
          } else {
            PortName_pair[i]->Text = "";
          }

          PortName_Changed(i);
        }

        Void UsePortsClass_GetChanges(int /*i*/, PortPair ^/*portChanges*/) {
        }

        Void UsePortsClass_Reset(int /*i*/) {
        }

        DeclareControlPairCheckBox(EmuBr)
        DeclareControlPairCheckBox(EmuOverrun)
        DeclareControlPairCheckBox(PlugInMode)
        DeclareControlPairCheckBox(ExclusiveMode)
        DeclareControlPairCheckBox(HiddenMode)

        #define ForEachControlPair(func) \
          PortName_##func; \
          UsePortsClass_##func; \
          EmuBr_##func; \
          EmuOverrun_##func; \
          PlugInMode_##func; \
          ExclusiveMode_##func; \
          HiddenMode_##func; \

    private:

        Void Reset() {
          pairList->BeginUpdate();

          for each (TreeNode ^pair in pairList->Nodes) {
            if (!pairs->ContainsKey(pair->Name) ||
                pairs[pair->Name][0] == nullptr ||
                pairs[pair->Name][1] == nullptr)
            {
              pairList->Nodes->Remove(pair);
            }
          }

          for each (KeyValuePair<String ^, PortPair ^> kvpPair in pairs) {
            if (kvpPair.Value[0] == nullptr || kvpPair.Value[1] == nullptr)
              continue;

            TreeNode ^pair;
            bool pairExpand;

            if (pairList->Nodes->ContainsKey(kvpPair.Key)) {
              pair = pairList->Nodes[kvpPair.Key];
              pairExpand = pair->IsExpanded;
            } else {
              pair = pairList->Nodes->Add(kvpPair.Key, String::Format(
                  "Virtual Port Pair {0}", kvpPair.Key));
              pairExpand = true;
            }

            bool portExpand[2];

            for (int i = 0 ; i < 2 ; i++) {
              try {
                portExpand[i] = pair->Nodes[i]->IsExpanded;
              }
              catch (Exception^ /*e*/) {
                portExpand[i] = false;
              }
            }

            pair->Nodes->Clear();

            for (int i = 0 ; i < 2 ; i++) {
              TreeNode ^port;

              try {
                String ^name = kvpPair.Value[i][(gcnew String("PortName"))->ToLower()];

                if (name == "COM#") {
                  try {
                    name = kvpPair.Value[i][(gcnew String("RealPortName"))->ToLower()];
                  }
                  catch (Exception^ /*e*/) {
                  }
                }

                port = pair->Nodes->Add(name);
              }
              catch (Exception^ /*e*/) {
                port = pair->Nodes->Add(String::Format("CNC{0}{1}", (i == 0) ? "A" : "B", kvpPair.Key));
              }

              for each (KeyValuePair<String ^, String ^> kvpPort in kvpPair.Value[i]) {
                port->Nodes->Add(String::Format("{0}={1}", kvpPort.Key, kvpPort.Value));
              }

              if (portExpand[i])
                port->Expand();
            }

            if (pairExpand)
              pair->Expand();
          }

          if (pairList->SelectedNode == nullptr) {
            try {
              pairList->SelectedNode = pairList->Nodes[0];
            }
            catch (Exception^ /*e*/) {
            }
          }

          pairList->EndUpdate();

          try {
            pinMap->Init(pairs[pairList->SelectedNode->Name]);
          }
          catch (Exception^ /*e*/) {
            pinMap->Init(nullptr);
          }

          picturePinMap->Invalidate();

          for (int i = 0 ; i < 2 ; i++) {
            ForEachControlPair(Reset(i))
          }
        }

        PortPair ^GetChanges() {
          PortPair ^portChanges = gcnew PortPair;

          pinMap->GetChanges(portChanges);

          for (int i = 0 ; i < 2 ; i++) {
            ForEachControlPair(GetChanges(i, portChanges))
          }

          return portChanges;
        }

        bool SaveChanges() {
          if (!pairList->SelectedNode)
            return true;

          PortPair ^portChanges = GetChanges();

          if (!portChanges->IsEmpty()) {
            String^ msg = String::Format(
                "The parameters of \"{0}\" were changed.\n"
                "Would you like to apply the changes?",
                pairList->SelectedNode->Text);

            System::Windows::Forms::DialogResult res;

            res = MessageBox::Show(this, msg, "Apply", MessageBoxButtons::YesNoCancel);

            if (res == System::Windows::Forms::DialogResult::Cancel) {
              return false;
            }
            else
            if (res == System::Windows::Forms::DialogResult::Yes) {
              pairs->ChangePair(pairList->SelectedNode->Name, portChanges);

              Reset();
            }
          }

          return true;
        }

	private:

        PinMap ^pinMap;
        PortPairs ^pairs;

    private:

        Void picturePinMap_Paint(Object ^/*sender*/, PaintEventArgs ^e) {
            pinMap->Paint(e, picturePinMap);
        }

        Void picturePinMap_MouseDown(Object ^/*sender*/, MouseEventArgs ^e) {
            pinMap->MouseDown(e);
            picturePinMap->Invalidate();
        }

        Void picturePinMap_MouseMove(Object ^/*sender*/, MouseEventArgs ^e) {
            pinMap->MouseMove(e);
            picturePinMap->Invalidate();
        }

        Void picturePinMap_MouseUp(Object ^/*sender*/, MouseEventArgs ^e) {
            pinMap->MouseUp(e);
            picturePinMap->Invalidate();
        }

        Void picturePinMap_MouseDoubleClick(Object ^/*sender*/, MouseEventArgs ^e) {
            pinMap->MouseDoubleClick(e);
            picturePinMap->Invalidate();
        }

        Void picturePinMap_MouseLeave(Object ^/*sender*/, EventArgs ^/*e*/) {
            pinMap->MouseInit();
            picturePinMap->Invalidate();
        }

    private:

        Void pairsList_BeforeSelect(Object ^/*sender*/, TreeViewCancelEventArgs ^e) {
          if (!SaveChanges())
            e->Cancel = true;
        }

        Void pairsList_AfterSelect(Object ^/*sender*/, TreeViewEventArgs ^/*e*/) {
          Reset();
        }

    private:

        Void buttonApply_Click(Object ^/*sender*/, EventArgs ^/*e*/) {
          if (pairList->SelectedNode) {
            pairs->ChangePair(pairList->SelectedNode->Name, GetChanges());
            Reset();
          }
        }

        Void buttonRemovePair_Click(Object ^/*sender*/, EventArgs ^/*e*/) {
          if (pairList->SelectedNode != nullptr) {
            String^ msg = String::Format(
                "Would you like to remove \"{0}\"?",
                pairList->SelectedNode->Text);

            System::Windows::Forms::DialogResult res;

            res = MessageBox::Show(this, msg, "", MessageBoxButtons::YesNo);

            if (res == System::Windows::Forms::DialogResult::Yes) {
              pairs->RemovePair(pairList->SelectedNode->Name);
              Reset();
            }
          }
        }

        Void buttonAddPair_Click(Object ^/*sender*/, EventArgs ^/*e*/) {
          if (!SaveChanges())
            return;

          String ^key = pairs->AddPair();

          Reset();

          try {
            pairList->SelectedNode = pairList->Nodes[key];
          }
          catch (Exception^ /*e*/) {
          }
        }

        Void buttonReset_Click(Object ^/*sender*/, EventArgs ^/*e*/) {
          pairs->Init();
          Reset();
        }
#pragma endregion

private: bool RC_isConnected, PSDR_isConnected;

private: Void this_Load(Object^ sender, EventArgs ^e) {
			 ForEachControlPair(Init())

				 pinMap = gcnew PinMap;
			 pairs = gcnew PortPairs(this);

			 pairs->Init();
			 Reset();
			 if(!InitialCom0ComSetup())
			 {
				 MessageBox::Show("При инициализации программы произошел сбой.\r\n Попробуйте перезапустить программу с правами администратора.");
			 }

			 array<Object^>^ objectArray = this->serialPSDR->GetPortNames();
			 comboBox1->Items->AddRange(objectArray);

 			 
		 }

private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 
		 }

private: bool checkListForOurPorts(String^ port1, String^ port2)
		 {
			 bool contais_portname=false;
			 String^ node_name="";

			 for each (TreeNode^ nodes in pairList->Nodes)
			 {
				 node_name = nodes->Name;
				 System::String^ pair_of_ports="";
				 for each (TreeNode^ n in nodes->Nodes)
				 {
					 pair_of_ports += n->ToString();
				 }
				 if (pair_of_ports->Contains(port1) && pair_of_ports->Contains(port2))
				 {
					 contais_portname=true;
				 }
				 else
				 {
					 if (pair_of_ports->Contains(port1) || pair_of_ports->Contains(port2))
					 {
						 pairs->RemovePair(node_name);
						 Reset();
					 }
				 }
			 }
			 return contais_portname;
		 }

private: bool InitialCom0ComSetup(){
			if (!SaveChanges())
				return false;

			if (checkListForOurPorts("COM98","COM99"))
			{
				return true;
			}
			String ^key;
			try {key = pairs->AddPair();} catch(...){return false;};

			Reset();

			try {
				pairList->SelectedNode = pairList->Nodes[key];
			}
			catch (Exception^ /*e*/) {
				return false;
			}

			try
			{
				PortNameA->Text	=	"COM98";
				PortNameB->Text	=	"COM99";
				EmuBrA->Checked=true;
				EmuBrB->Checked=true;
				HiddenModeA->Checked=true;
				HiddenModeB->Checked=true;
				ExclusiveModeA->Checked=true;
				ExclusiveModeB->Checked=true;

				if (pairList->SelectedNode) {
					pairs->ChangePair(pairList->SelectedNode->Name, GetChanges());
					Reset();
				}
			}
			catch (...)
			{
				return false;
			};
			

			return true;
		 };


private: System::Void buttonConnect_Click(System::Object^  sender, System::EventArgs^  e) {
			 serialRC->Close();
			 serialRC->PortName=comboBox1->Text;
			 try{serialRC->Open();} catch (...){};
		 }

private: System::Void timerOpenPorts_Tick(System::Object^  sender, System::EventArgs^  e) {
			 if (!serialPSDR->IsOpen)
			 {
				 serialPSDR->Close();
				 try{serialPSDR->Open();} catch (...){};
			 }

			 checkBoxPSDR->Checked=PSDR_isConnected;
			 PSDR_isConnected=false;

			 if (serialPSDR->IsOpen)
			 {
		 		 try {serialPSDR->WriteLine("ZZFA;");} catch(...){};
			 }

			 //пульт
			 if ((!serialRC->IsOpen || serialRC->PortName!=comboBox1->Text || !RC_isConnected) && (this->WindowState != FormWindowState::Normal))
			 {
				 serialRC->Close();
				 serialRC->PortName=comboBox1->Text;
				 try{serialRC->Open();} catch (...){};
				 label1->Text = " порт открыт";
			 }

			 checkBoxRC->Checked=RC_isConnected;
			 RC_isConnected=false;

			 if (serialRC->IsOpen)
			 {
				 label1->Text = " порт открыт";
				 array<Byte,1>^ mess = gcnew array<Byte,1>(4);
				 mess[0]=0xC9;
				 mess[1]=0x00;
				 mess[2]=0x00;
				 mess[3]=0x03;
				 try {serialRC->Write(mess,0,4);} catch(...){};
			 }

		 }

private: System::Void timerReadRC_Tick(System::Object^  sender, System::EventArgs^  e) {
			 if (!serialRC->IsOpen) {return;}

			 int BTR = serialRC->BytesToRead;
			 if (BTR==0) return;
			 RC_isConnected=true;

			 array<Byte,1>^ messages= gcnew array<Byte,1>(BTR);
			 serialRC->Read(messages,0,BTR);

			 textBox1->Text = Convert::ToString(messages[BTR-1]) + "\r\n" + textBox1->Text;
		 }
private: void show_hide_Form1(bool state){
			 if (state)
			 {
				 this->Visible=false;
				 //this->WindowState=FormWindowState::Minimized;
			 }
			 else
			 {
				 this->Visible=true;
				 this->WindowState=FormWindowState::Normal;
			 }
		 }

private: System::Void notifyIcon_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 show_hide_Form1(false);
		 }
private: System::Void Form1_SizeChanged(System::Object^  sender, System::EventArgs^  e) {

			 if (this->WindowState == FormWindowState::Minimized)
			 {
				 show_hide_Form1(true);
			 }
			 else
			 {
				 show_hide_Form1(false);
			 }

		 }
private: System::Void Form1_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
			 System::Windows::Forms::DialogResult diag_res = MessageBox::Show("Вы уверены что хотите завершить работу приложения TuneSDR.com?","Выход?",MessageBoxButtons::OKCancel);

			 if (diag_res == System::Windows::Forms::DialogResult::Cancel)
			 {
				 e->Cancel=true;
			 }
			 else
			 {
				 serialPSDR->Close();
				 serialRC->Close();
			 }

			 
		 }
private: System::Void button1_Click_1(System::Object^  sender, System::EventArgs^  e) {
			 InitialCom0ComSetup();
		 }

};
}
