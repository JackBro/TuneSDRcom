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
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "PultToPowersdrProvider.h"
#include "PowersdrToPultProvider.h"
#include "PowersdrAsker.h"

#define POWERSDR_IN_PORT "COM28"
#define POWERSDR_OUT_PORT "COM29"

#pragma comment(lib, "user32.lib")

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
	using namespace System::IO;

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

			RC_isConnected=false;
			PSDR_isConnected=false;

			AccelerationSteps = gcnew array<System::String^,1>(15);
			AccelerationSteps[0]	="1 Hz";
			AccelerationSteps[1]	="10 Hz";
			AccelerationSteps[2]	="50 Hz";
			AccelerationSteps[3]	="100 Hz";
			AccelerationSteps[4]	="250 Hz";
			AccelerationSteps[5]	="500 Hz";
			AccelerationSteps[6]	="1 KHz";
			AccelerationSteps[7]	="5 KHz";
			AccelerationSteps[8]	="9 KHz";
			AccelerationSteps[9]	="10 KHz";
			AccelerationSteps[10]	="100 KHz";
			AccelerationSteps[11]	="250 KHz";
			AccelerationSteps[12]	="500 KHz";
			AccelerationSteps[13]	="1 MHz";
			AccelerationSteps[14]	="10 MHz";

			pttOld=0;
		}

	protected:
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







	private: System::IO::Ports::SerialPort^  serialRC;
	private: System::IO::Ports::SerialPort^  serialPSDR;
	private: System::Windows::Forms::ComboBox^  cbPortName;



	private: System::Windows::Forms::Timer^  timerOpenPorts;
	private: System::Windows::Forms::Timer^  timerReadRC;
	private: System::Windows::Forms::NotifyIcon^  notifyIcon;






	private: System::Windows::Forms::Timer^  timerReadPSDR;

	private: System::Windows::Forms::Timer^  timerPsdrAsker;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripPower;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripTune;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripPult;
	private: System::Windows::Forms::ToolStripSplitButton^  toolStripSplitButton1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::CheckBox^  cbManualConnect;
	private: System::Windows::Forms::CheckBox^  cbAutostart;
	private: System::Windows::Forms::CheckBox^  cbAskQuit;
	private: System::Windows::Forms::CheckBox^  cbMinToTray;
	private: System::Windows::Forms::CheckBox^  cbMinOnStart;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TabPage^  tabPage3;
private: System::Windows::Forms::TrackBar^  trackAccel5;

private: System::Windows::Forms::TrackBar^  trackAccel1;
private: System::Windows::Forms::TrackBar^  trackAccel2;
private: System::Windows::Forms::TrackBar^  trackAccel3;
private: System::Windows::Forms::TrackBar^  trackAccel4;




	private: System::Windows::Forms::Label^  label15;
private: System::Windows::Forms::Label^  labelAccel5;

private: System::Windows::Forms::Label^  labelAccel4;

private: System::Windows::Forms::Label^  labelAccel3;

private: System::Windows::Forms::Label^  labelAccel2;

private: System::Windows::Forms::Label^  labelAccel1;

	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label3;
private: System::Windows::Forms::Button^  BtnAccelDefaults;
private: System::Windows::Forms::ContextMenuStrip^  contextMenuStrip1;
private: System::Windows::Forms::ToolStripMenuItem^  íàñòðîéêèToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  ñàéòÏðîåêòàToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  âûõîäToolStripMenuItem;
private: System::Windows::Forms::TabPage^  tabPage4;
private: System::Windows::Forms::NumericUpDown^  numericFilterStep;

private: System::Windows::Forms::Label^  label10;
private: System::Windows::Forms::Label^  label9;
private: System::Windows::Forms::Label^  label8;
private: System::Windows::Forms::NumericUpDown^  numericRitXit;

private: System::Windows::Forms::Label^  label11;
private: System::Windows::Forms::Label^  label12;
private: System::Windows::Forms::Button^  btnResetRitXit;

private: System::Windows::Forms::Button^  btnResetFilterStep;
private: System::Windows::Forms::TabPage^  tabPage5;
private: System::Windows::Forms::Label^  label13;

private: System::Windows::Forms::GroupBox^  groupBox1;
private: System::Windows::Forms::TextBox^  tbF_first;

private: System::Windows::Forms::GroupBox^  groupBox3;
private: System::Windows::Forms::TextBox^  tbF_second;
private: System::Windows::Forms::Timer^  timerPTT;
private: System::Windows::Forms::CheckBox^  cbUseFreqAcc;
private: System::Windows::Forms::Panel^  panelFreqAcc;
private: System::Windows::Forms::Label^  label14;
private: System::Windows::Forms::TrackBar^  trackAccel0;
private: System::Windows::Forms::Label^  labelAccel0;
private: System::Windows::Forms::ComboBox^  cbSmMatrix;
private: System::Windows::Forms::Label^  label16;










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
			this->cbPortName = (gcnew System::Windows::Forms::ComboBox());
			this->serialRC = (gcnew System::IO::Ports::SerialPort(this->components));
			this->serialPSDR = (gcnew System::IO::Ports::SerialPort(this->components));
			this->timerOpenPorts = (gcnew System::Windows::Forms::Timer(this->components));
			this->timerReadRC = (gcnew System::Windows::Forms::Timer(this->components));
			this->notifyIcon = (gcnew System::Windows::Forms::NotifyIcon(this->components));
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->íàñòðîéêèToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ñàéòÏðîåêòàToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->âûõîäToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->timerReadPSDR = (gcnew System::Windows::Forms::Timer(this->components));
			this->timerPsdrAsker = (gcnew System::Windows::Forms::Timer(this->components));
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->cbSmMatrix = (gcnew System::Windows::Forms::ComboBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->cbMinOnStart = (gcnew System::Windows::Forms::CheckBox());
			this->cbMinToTray = (gcnew System::Windows::Forms::CheckBox());
			this->cbAskQuit = (gcnew System::Windows::Forms::CheckBox());
			this->cbManualConnect = (gcnew System::Windows::Forms::CheckBox());
			this->cbAutostart = (gcnew System::Windows::Forms::CheckBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->panelFreqAcc = (gcnew System::Windows::Forms::Panel());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->trackAccel0 = (gcnew System::Windows::Forms::TrackBar());
			this->labelAccel0 = (gcnew System::Windows::Forms::Label());
			this->trackAccel1 = (gcnew System::Windows::Forms::TrackBar());
			this->trackAccel3 = (gcnew System::Windows::Forms::TrackBar());
			this->trackAccel2 = (gcnew System::Windows::Forms::TrackBar());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->labelAccel5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->labelAccel4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->labelAccel3 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->labelAccel1 = (gcnew System::Windows::Forms::Label());
			this->trackAccel5 = (gcnew System::Windows::Forms::TrackBar());
			this->labelAccel2 = (gcnew System::Windows::Forms::Label());
			this->trackAccel4 = (gcnew System::Windows::Forms::TrackBar());
			this->cbUseFreqAcc = (gcnew System::Windows::Forms::CheckBox());
			this->BtnAccelDefaults = (gcnew System::Windows::Forms::Button());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
			this->btnResetRitXit = (gcnew System::Windows::Forms::Button());
			this->btnResetFilterStep = (gcnew System::Windows::Forms::Button());
			this->numericRitXit = (gcnew System::Windows::Forms::NumericUpDown());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->numericFilterStep = (gcnew System::Windows::Forms::NumericUpDown());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->tabPage5 = (gcnew System::Windows::Forms::TabPage());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->tbF_second = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->tbF_first = (gcnew System::Windows::Forms::TextBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripPower = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripTune = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripPult = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripSplitButton1 = (gcnew System::Windows::Forms::ToolStripSplitButton());
			this->timerPTT = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picturePinMap))->BeginInit();
			this->contextMenuStrip1->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->panelFreqAcc->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackAccel0))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackAccel1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackAccel3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackAccel2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackAccel5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackAccel4))->BeginInit();
			this->tabPage4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericRitXit))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericFilterStep))->BeginInit();
			this->tabPage5->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->statusStrip1->SuspendLayout();
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
			// cbPortName
			// 
			this->cbPortName->FormattingEnabled = true;
			resources->ApplyResources(this->cbPortName, L"cbPortName");
			this->cbPortName->Name = L"cbPortName";
			this->cbPortName->Click += gcnew System::EventHandler(this, &Form1::cbPortName_Click);
			// 
			// serialRC
			// 
			this->serialRC->BaudRate = 115200;
			this->serialRC->ReadTimeout = 5;
			this->serialRC->WriteTimeout = 5;
			// 
			// serialPSDR
			// 
			this->serialPSDR->BaudRate = 19200;
			this->serialPSDR->PortName = L"COM98";
			this->serialPSDR->ReadTimeout = 50;
			this->serialPSDR->WriteTimeout = 50;
			// 
			// timerOpenPorts
			// 
			this->timerOpenPorts->Interval = 3000;
			this->timerOpenPorts->Tick += gcnew System::EventHandler(this, &Form1::timerOpenPorts_Tick);
			// 
			// timerReadRC
			// 
			this->timerReadRC->Tick += gcnew System::EventHandler(this, &Form1::timerReadRC_Tick);
			// 
			// notifyIcon
			// 
			this->notifyIcon->ContextMenuStrip = this->contextMenuStrip1;
			resources->ApplyResources(this->notifyIcon, L"notifyIcon");
			this->notifyIcon->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::notifyIcon_MouseClick);
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->íàñòðîéêèToolStripMenuItem, 
				this->ñàéòÏðîåêòàToolStripMenuItem, this->âûõîäToolStripMenuItem});
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			resources->ApplyResources(this->contextMenuStrip1, L"contextMenuStrip1");
			// 
			// íàñòðîéêèToolStripMenuItem
			// 
			resources->ApplyResources(this->íàñòðîéêèToolStripMenuItem, L"íàñòðîéêèToolStripMenuItem");
			this->íàñòðîéêèToolStripMenuItem->Name = L"íàñòðîéêèToolStripMenuItem";
			this->íàñòðîéêèToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::íàñòðîéêèToolStripMenuItem_Click);
			// 
			// ñàéòÏðîåêòàToolStripMenuItem
			// 
			resources->ApplyResources(this->ñàéòÏðîåêòàToolStripMenuItem, L"ñàéòÏðîåêòàToolStripMenuItem");
			this->ñàéòÏðîåêòàToolStripMenuItem->Name = L"ñàéòÏðîåêòàToolStripMenuItem";
			this->ñàéòÏðîåêòàToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::ñàéòÏðîåêòàToolStripMenuItem_Click);
			// 
			// âûõîäToolStripMenuItem
			// 
			resources->ApplyResources(this->âûõîäToolStripMenuItem, L"âûõîäToolStripMenuItem");
			this->âûõîäToolStripMenuItem->Name = L"âûõîäToolStripMenuItem";
			this->âûõîäToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::âûõîäToolStripMenuItem_Click);
			// 
			// timerReadPSDR
			// 
			this->timerReadPSDR->Tick += gcnew System::EventHandler(this, &Form1::timerReadPSDR_Tick);
			// 
			// timerPsdrAsker
			// 
			this->timerPsdrAsker->Interval = 111;
			this->timerPsdrAsker->Tick += gcnew System::EventHandler(this, &Form1::timerPsdrAsker_Tick);
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Controls->Add(this->tabPage4);
			this->tabControl1->Controls->Add(this->tabPage5);
			this->tabControl1->Controls->Add(this->tabPage2);
			resources->ApplyResources(this->tabControl1, L"tabControl1");
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			// 
			// tabPage1
			// 
			this->tabPage1->BackColor = System::Drawing::Color::WhiteSmoke;
			this->tabPage1->Controls->Add(this->label16);
			this->tabPage1->Controls->Add(this->cbSmMatrix);
			this->tabPage1->Controls->Add(this->label2);
			this->tabPage1->Controls->Add(this->cbMinOnStart);
			this->tabPage1->Controls->Add(this->cbMinToTray);
			this->tabPage1->Controls->Add(this->cbAskQuit);
			this->tabPage1->Controls->Add(this->cbManualConnect);
			this->tabPage1->Controls->Add(this->cbAutostart);
			this->tabPage1->Controls->Add(this->label1);
			this->tabPage1->Controls->Add(this->cbPortName);
			resources->ApplyResources(this->tabPage1, L"tabPage1");
			this->tabPage1->Name = L"tabPage1";
			// 
			// label16
			// 
			resources->ApplyResources(this->label16, L"label16");
			this->label16->Name = L"label16";
			// 
			// cbSmMatrix
			// 
			this->cbSmMatrix->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbSmMatrix->FormattingEnabled = true;
			resources->ApplyResources(this->cbSmMatrix, L"cbSmMatrix");
			this->cbSmMatrix->Name = L"cbSmMatrix";
			this->cbSmMatrix->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::cbSmMatrix_SelectedIndexChanged);
			// 
			// label2
			// 
			resources->ApplyResources(this->label2, L"label2");
			this->label2->Name = L"label2";
			// 
			// cbMinOnStart
			// 
			resources->ApplyResources(this->cbMinOnStart, L"cbMinOnStart");
			this->cbMinOnStart->Checked = true;
			this->cbMinOnStart->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cbMinOnStart->Name = L"cbMinOnStart";
			this->cbMinOnStart->UseVisualStyleBackColor = true;
			// 
			// cbMinToTray
			// 
			resources->ApplyResources(this->cbMinToTray, L"cbMinToTray");
			this->cbMinToTray->Checked = true;
			this->cbMinToTray->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cbMinToTray->Name = L"cbMinToTray";
			this->cbMinToTray->UseVisualStyleBackColor = true;
			// 
			// cbAskQuit
			// 
			resources->ApplyResources(this->cbAskQuit, L"cbAskQuit");
			this->cbAskQuit->Checked = true;
			this->cbAskQuit->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cbAskQuit->Name = L"cbAskQuit";
			this->cbAskQuit->UseVisualStyleBackColor = true;
			// 
			// cbManualConnect
			// 
			resources->ApplyResources(this->cbManualConnect, L"cbManualConnect");
			this->cbManualConnect->Name = L"cbManualConnect";
			this->cbManualConnect->UseVisualStyleBackColor = true;
			// 
			// cbAutostart
			// 
			resources->ApplyResources(this->cbAutostart, L"cbAutostart");
			this->cbAutostart->Name = L"cbAutostart";
			this->cbAutostart->UseVisualStyleBackColor = true;
			this->cbAutostart->CheckedChanged += gcnew System::EventHandler(this, &Form1::cbAutostart_CheckedChanged);
			// 
			// label1
			// 
			resources->ApplyResources(this->label1, L"label1");
			this->label1->Name = L"label1";
			// 
			// tabPage3
			// 
			this->tabPage3->BackColor = System::Drawing::Color::WhiteSmoke;
			this->tabPage3->Controls->Add(this->panelFreqAcc);
			this->tabPage3->Controls->Add(this->cbUseFreqAcc);
			this->tabPage3->Controls->Add(this->BtnAccelDefaults);
			this->tabPage3->Controls->Add(this->label15);
			resources->ApplyResources(this->tabPage3, L"tabPage3");
			this->tabPage3->Name = L"tabPage3";
			// 
			// panelFreqAcc
			// 
			this->panelFreqAcc->Controls->Add(this->label14);
			this->panelFreqAcc->Controls->Add(this->trackAccel0);
			this->panelFreqAcc->Controls->Add(this->labelAccel0);
			this->panelFreqAcc->Controls->Add(this->trackAccel1);
			this->panelFreqAcc->Controls->Add(this->trackAccel3);
			this->panelFreqAcc->Controls->Add(this->trackAccel2);
			this->panelFreqAcc->Controls->Add(this->label3);
			this->panelFreqAcc->Controls->Add(this->labelAccel5);
			this->panelFreqAcc->Controls->Add(this->label4);
			this->panelFreqAcc->Controls->Add(this->labelAccel4);
			this->panelFreqAcc->Controls->Add(this->label5);
			this->panelFreqAcc->Controls->Add(this->label7);
			this->panelFreqAcc->Controls->Add(this->labelAccel3);
			this->panelFreqAcc->Controls->Add(this->label6);
			this->panelFreqAcc->Controls->Add(this->labelAccel1);
			this->panelFreqAcc->Controls->Add(this->trackAccel5);
			this->panelFreqAcc->Controls->Add(this->labelAccel2);
			this->panelFreqAcc->Controls->Add(this->trackAccel4);
			resources->ApplyResources(this->panelFreqAcc, L"panelFreqAcc");
			this->panelFreqAcc->Name = L"panelFreqAcc";
			// 
			// label14
			// 
			resources->ApplyResources(this->label14, L"label14");
			this->label14->Name = L"label14";
			// 
			// trackAccel0
			// 
			resources->ApplyResources(this->trackAccel0, L"trackAccel0");
			this->trackAccel0->LargeChange = 1;
			this->trackAccel0->Maximum = 14;
			this->trackAccel0->Name = L"trackAccel0";
			this->trackAccel0->Value = 1;
			this->trackAccel0->Scroll += gcnew System::EventHandler(this, &Form1::trackAccel0_Scroll);
			// 
			// labelAccel0
			// 
			resources->ApplyResources(this->labelAccel0, L"labelAccel0");
			this->labelAccel0->Name = L"labelAccel0";
			// 
			// trackAccel1
			// 
			resources->ApplyResources(this->trackAccel1, L"trackAccel1");
			this->trackAccel1->LargeChange = 1;
			this->trackAccel1->Maximum = 14;
			this->trackAccel1->Name = L"trackAccel1";
			this->trackAccel1->Value = 1;
			this->trackAccel1->Scroll += gcnew System::EventHandler(this, &Form1::trackAccel1_Scroll);
			// 
			// trackAccel3
			// 
			resources->ApplyResources(this->trackAccel3, L"trackAccel3");
			this->trackAccel3->LargeChange = 1;
			this->trackAccel3->Maximum = 14;
			this->trackAccel3->Name = L"trackAccel3";
			this->trackAccel3->Value = 2;
			this->trackAccel3->Scroll += gcnew System::EventHandler(this, &Form1::trackAccel3_Scroll);
			// 
			// trackAccel2
			// 
			resources->ApplyResources(this->trackAccel2, L"trackAccel2");
			this->trackAccel2->LargeChange = 1;
			this->trackAccel2->Maximum = 14;
			this->trackAccel2->Name = L"trackAccel2";
			this->trackAccel2->Value = 1;
			this->trackAccel2->Scroll += gcnew System::EventHandler(this, &Form1::trackAccel2_Scroll);
			// 
			// label3
			// 
			resources->ApplyResources(this->label3, L"label3");
			this->label3->Name = L"label3";
			// 
			// labelAccel5
			// 
			resources->ApplyResources(this->labelAccel5, L"labelAccel5");
			this->labelAccel5->Name = L"labelAccel5";
			// 
			// label4
			// 
			resources->ApplyResources(this->label4, L"label4");
			this->label4->Name = L"label4";
			// 
			// labelAccel4
			// 
			resources->ApplyResources(this->labelAccel4, L"labelAccel4");
			this->labelAccel4->Name = L"labelAccel4";
			// 
			// label5
			// 
			resources->ApplyResources(this->label5, L"label5");
			this->label5->Name = L"label5";
			// 
			// label7
			// 
			resources->ApplyResources(this->label7, L"label7");
			this->label7->Name = L"label7";
			// 
			// labelAccel3
			// 
			resources->ApplyResources(this->labelAccel3, L"labelAccel3");
			this->labelAccel3->Name = L"labelAccel3";
			// 
			// label6
			// 
			resources->ApplyResources(this->label6, L"label6");
			this->label6->Name = L"label6";
			// 
			// labelAccel1
			// 
			resources->ApplyResources(this->labelAccel1, L"labelAccel1");
			this->labelAccel1->Name = L"labelAccel1";
			// 
			// trackAccel5
			// 
			resources->ApplyResources(this->trackAccel5, L"trackAccel5");
			this->trackAccel5->LargeChange = 1;
			this->trackAccel5->Maximum = 14;
			this->trackAccel5->Name = L"trackAccel5";
			this->trackAccel5->Value = 4;
			this->trackAccel5->Scroll += gcnew System::EventHandler(this, &Form1::trackAccel5_Scroll);
			// 
			// labelAccel2
			// 
			resources->ApplyResources(this->labelAccel2, L"labelAccel2");
			this->labelAccel2->Name = L"labelAccel2";
			// 
			// trackAccel4
			// 
			resources->ApplyResources(this->trackAccel4, L"trackAccel4");
			this->trackAccel4->LargeChange = 1;
			this->trackAccel4->Maximum = 14;
			this->trackAccel4->Name = L"trackAccel4";
			this->trackAccel4->Value = 3;
			this->trackAccel4->Scroll += gcnew System::EventHandler(this, &Form1::trackAccel4_Scroll);
			// 
			// cbUseFreqAcc
			// 
			resources->ApplyResources(this->cbUseFreqAcc, L"cbUseFreqAcc");
			this->cbUseFreqAcc->Name = L"cbUseFreqAcc";
			this->cbUseFreqAcc->UseVisualStyleBackColor = true;
			this->cbUseFreqAcc->CheckedChanged += gcnew System::EventHandler(this, &Form1::cbUseFreqAcc_CheckedChanged);
			// 
			// BtnAccelDefaults
			// 
			resources->ApplyResources(this->BtnAccelDefaults, L"BtnAccelDefaults");
			this->BtnAccelDefaults->Name = L"BtnAccelDefaults";
			this->BtnAccelDefaults->UseVisualStyleBackColor = true;
			this->BtnAccelDefaults->Click += gcnew System::EventHandler(this, &Form1::BtnAccelDefaults_Click);
			// 
			// label15
			// 
			resources->ApplyResources(this->label15, L"label15");
			this->label15->Name = L"label15";
			// 
			// tabPage4
			// 
			this->tabPage4->BackColor = System::Drawing::Color::WhiteSmoke;
			this->tabPage4->Controls->Add(this->btnResetRitXit);
			this->tabPage4->Controls->Add(this->btnResetFilterStep);
			this->tabPage4->Controls->Add(this->numericRitXit);
			this->tabPage4->Controls->Add(this->label11);
			this->tabPage4->Controls->Add(this->label12);
			this->tabPage4->Controls->Add(this->numericFilterStep);
			this->tabPage4->Controls->Add(this->label10);
			this->tabPage4->Controls->Add(this->label9);
			this->tabPage4->Controls->Add(this->label8);
			resources->ApplyResources(this->tabPage4, L"tabPage4");
			this->tabPage4->Name = L"tabPage4";
			// 
			// btnResetRitXit
			// 
			resources->ApplyResources(this->btnResetRitXit, L"btnResetRitXit");
			this->btnResetRitXit->Name = L"btnResetRitXit";
			this->btnResetRitXit->UseVisualStyleBackColor = true;
			this->btnResetRitXit->Click += gcnew System::EventHandler(this, &Form1::btnResetRitXit_Click);
			// 
			// btnResetFilterStep
			// 
			resources->ApplyResources(this->btnResetFilterStep, L"btnResetFilterStep");
			this->btnResetFilterStep->Name = L"btnResetFilterStep";
			this->btnResetFilterStep->UseVisualStyleBackColor = true;
			this->btnResetFilterStep->Click += gcnew System::EventHandler(this, &Form1::btnResetFilterStep_Click);
			// 
			// numericRitXit
			// 
			this->numericRitXit->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {10, 0, 0, 0});
			resources->ApplyResources(this->numericRitXit, L"numericRitXit");
			this->numericRitXit->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {250, 0, 0, 0});
			this->numericRitXit->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->numericRitXit->Name = L"numericRitXit";
			this->numericRitXit->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {100, 0, 0, 0});
			// 
			// label11
			// 
			resources->ApplyResources(this->label11, L"label11");
			this->label11->Name = L"label11";
			// 
			// label12
			// 
			resources->ApplyResources(this->label12, L"label12");
			this->label12->Name = L"label12";
			// 
			// numericFilterStep
			// 
			this->numericFilterStep->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {10, 0, 0, 0});
			resources->ApplyResources(this->numericFilterStep, L"numericFilterStep");
			this->numericFilterStep->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {250, 0, 0, 0});
			this->numericFilterStep->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->numericFilterStep->Name = L"numericFilterStep";
			this->numericFilterStep->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {100, 0, 0, 0});
			// 
			// label10
			// 
			resources->ApplyResources(this->label10, L"label10");
			this->label10->Name = L"label10";
			// 
			// label9
			// 
			resources->ApplyResources(this->label9, L"label9");
			this->label9->Name = L"label9";
			// 
			// label8
			// 
			resources->ApplyResources(this->label8, L"label8");
			this->label8->Name = L"label8";
			// 
			// tabPage5
			// 
			this->tabPage5->BackColor = System::Drawing::Color::WhiteSmoke;
			this->tabPage5->Controls->Add(this->groupBox3);
			this->tabPage5->Controls->Add(this->groupBox1);
			this->tabPage5->Controls->Add(this->label13);
			resources->ApplyResources(this->tabPage5, L"tabPage5");
			this->tabPage5->Name = L"tabPage5";
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->tbF_second);
			resources->ApplyResources(this->groupBox3, L"groupBox3");
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->TabStop = false;
			// 
			// tbF_second
			// 
			this->tbF_second->BackColor = System::Drawing::SystemColors::Control;
			this->tbF_second->BorderStyle = System::Windows::Forms::BorderStyle::None;
			resources->ApplyResources(this->tbF_second, L"tbF_second");
			this->tbF_second->Name = L"tbF_second";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->tbF_first);
			resources->ApplyResources(this->groupBox1, L"groupBox1");
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->TabStop = false;
			// 
			// tbF_first
			// 
			this->tbF_first->BackColor = System::Drawing::SystemColors::Control;
			this->tbF_first->BorderStyle = System::Windows::Forms::BorderStyle::None;
			resources->ApplyResources(this->tbF_first, L"tbF_first");
			this->tbF_first->Name = L"tbF_first";
			// 
			// label13
			// 
			resources->ApplyResources(this->label13, L"label13");
			this->label13->Name = L"label13";
			// 
			// tabPage2
			// 
			this->tabPage2->BackColor = System::Drawing::Color::WhiteSmoke;
			this->tabPage2->Controls->Add(this->pairList);
			this->tabPage2->Controls->Add(this->picturePinMap);
			this->tabPage2->Controls->Add(this->UsePortsClassA);
			this->tabPage2->Controls->Add(this->pinNameON);
			this->tabPage2->Controls->Add(this->UsePortsClassB);
			this->tabPage2->Controls->Add(this->PortNameA);
			this->tabPage2->Controls->Add(this->HiddenModeA);
			this->tabPage2->Controls->Add(this->PortNameB);
			this->tabPage2->Controls->Add(this->HiddenModeB);
			this->tabPage2->Controls->Add(this->buttonRemovePair);
			this->tabPage2->Controls->Add(this->pinNameB_OPEN);
			this->tabPage2->Controls->Add(this->buttonAddPair);
			this->tabPage2->Controls->Add(this->pinNameB_OUT1);
			this->tabPage2->Controls->Add(this->buttonApply);
			this->tabPage2->Controls->Add(this->pinNameB_OUT2);
			this->tabPage2->Controls->Add(this->buttonReset);
			this->tabPage2->Controls->Add(this->pinNameB_RI);
			this->tabPage2->Controls->Add(this->EmuBrB);
			this->tabPage2->Controls->Add(this->pinNameB_CTS);
			this->tabPage2->Controls->Add(this->EmuOverrunB);
			this->tabPage2->Controls->Add(this->pinNameB_RTS);
			this->tabPage2->Controls->Add(this->PlugInModeB);
			this->tabPage2->Controls->Add(this->pinNameB_DCD);
			this->tabPage2->Controls->Add(this->ExclusiveModeB);
			this->tabPage2->Controls->Add(this->pinNameB_DSR);
			this->tabPage2->Controls->Add(this->EmuBrA);
			this->tabPage2->Controls->Add(this->pinNameB_TX);
			this->tabPage2->Controls->Add(this->EmuOverrunA);
			this->tabPage2->Controls->Add(this->pinNameB_DTR);
			this->tabPage2->Controls->Add(this->PlugInModeA);
			this->tabPage2->Controls->Add(this->pinNameB_RX);
			this->tabPage2->Controls->Add(this->ExclusiveModeA);
			this->tabPage2->Controls->Add(this->pinNameA_OPEN);
			this->tabPage2->Controls->Add(this->pinNameA_RX);
			this->tabPage2->Controls->Add(this->pinNameA_OUT1);
			this->tabPage2->Controls->Add(this->pinNameA_DTR);
			this->tabPage2->Controls->Add(this->pinNameA_OUT2);
			this->tabPage2->Controls->Add(this->pinNameA_TX);
			this->tabPage2->Controls->Add(this->pinNameA_RI);
			this->tabPage2->Controls->Add(this->pinNameA_DSR);
			this->tabPage2->Controls->Add(this->pinNameA_CTS);
			this->tabPage2->Controls->Add(this->pinNameA_DCD);
			this->tabPage2->Controls->Add(this->pinNameA_RTS);
			resources->ApplyResources(this->tabPage2, L"tabPage2");
			this->tabPage2->Name = L"tabPage2";
			// 
			// statusStrip1
			// 
			this->statusStrip1->BackColor = System::Drawing::Color::WhiteSmoke;
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->toolStripPower, 
				this->toolStripTune, this->toolStripPult, this->toolStripSplitButton1});
			this->statusStrip1->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::HorizontalStackWithOverflow;
			resources->ApplyResources(this->statusStrip1, L"statusStrip1");
			this->statusStrip1->Name = L"statusStrip1";
			// 
			// toolStripPower
			// 
			this->toolStripPower->Name = L"toolStripPower";
			resources->ApplyResources(this->toolStripPower, L"toolStripPower");
			// 
			// toolStripTune
			// 
			this->toolStripTune->Name = L"toolStripTune";
			resources->ApplyResources(this->toolStripTune, L"toolStripTune");
			// 
			// toolStripPult
			// 
			this->toolStripPult->Name = L"toolStripPult";
			resources->ApplyResources(this->toolStripPult, L"toolStripPult");
			// 
			// toolStripSplitButton1
			// 
			this->toolStripSplitButton1->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
			this->toolStripSplitButton1->BackColor = System::Drawing::Color::Transparent;
			this->toolStripSplitButton1->DropDownButtonWidth = 0;
			this->toolStripSplitButton1->ForeColor = System::Drawing::SystemColors::ControlText;
			resources->ApplyResources(this->toolStripSplitButton1, L"toolStripSplitButton1");
			this->toolStripSplitButton1->Name = L"toolStripSplitButton1";
			this->toolStripSplitButton1->ButtonClick += gcnew System::EventHandler(this, &Form1::buttonConnect_Click);
			// 
			// timerPTT
			// 
			this->timerPTT->Interval = 200;
			this->timerPTT->Tick += gcnew System::EventHandler(this, &Form1::timerPTT_Tick);
			// 
			// Form1
			// 
			resources->ApplyResources(this, L"$this");
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->tabControl1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"Form1";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::Form1_FormClosing);
			this->Load += gcnew System::EventHandler(this, &Form1::this_Load);
			this->Resize += gcnew System::EventHandler(this, &Form1::Form1_Resize);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picturePinMap))->EndInit();
			this->contextMenuStrip1->ResumeLayout(false);
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->tabPage3->ResumeLayout(false);
			this->tabPage3->PerformLayout();
			this->panelFreqAcc->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackAccel0))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackAccel1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackAccel3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackAccel2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackAccel5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackAccel4))->EndInit();
			this->tabPage4->ResumeLayout(false);
			this->tabPage4->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericRitXit))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericFilterStep))->EndInit();
			this->tabPage5->ResumeLayout(false);
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
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

            //res = MessageBox::Show(this, msg, "Apply", MessageBoxButtons::YesNoCancel);

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
			if (pairList->SelectedNode->Text->Remove(0,18) == Convert::ToString(com0comPair))
			{
				MessageBox::Show("Íåâîçìîæíî èçìåíÿòü ïàðó êîòîðàÿ èñïîëüçóåòñÿ ïðîãðàììîé");
				return;
			}
          if (pairList->SelectedNode) {
            pairs->ChangePair(pairList->SelectedNode->Name, GetChanges());
            Reset();
          }
        }

        Void buttonRemovePair_Click(Object ^/*sender*/, EventArgs ^/*e*/) {
			if (pairList->SelectedNode->Text->Remove(0,18) == Convert::ToString(com0comPair))
			{
				MessageBox::Show("Íåâîçìîæíî óäàëèòü ïàðó êîòîðàÿ èñïîëüçóåòñÿ ïðîãðàììîé");
				return;
			}

          if (pairList->SelectedNode != nullptr) {
            String^ msg = String::Format(
                "Âû õîòèòå óäàëèòü \"{0}\"?",
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
private: bool CloseWithoutAsking,MinimizeOnLaunch;

private: int com0comPair;
private: array<System::String^,1>^ AccelerationSteps;
private: int pttOld;

List<String^> sm_paths;

private: PultToPowersdrProvider PuPoProvider;
private: PowersdrToPultProvider PoPuProvider;
private: PowersdrAsker PowerAsker;
private: PowersdrButtonStates PowerBtnStates;


#pragma region Settings
private: void WriteSettings(void){
			 try
			 {
				 FileStream^ f_stream = gcnew FileStream(System::IO::Path::GetDirectoryName(System::Windows::Forms::Application::ExecutablePath)+"\\settings.cfg", FileMode::Create);
				 BinaryWriter^ bw = gcnew BinaryWriter(f_stream);

				 bw->Write(cbPortName->Text);
				 bw->Write(com0comPair);
				 bw->Write(cbAutostart->Checked);
				 bw->Write(cbManualConnect->Checked);
				 bw->Write(cbMinToTray->Checked);
				 bw->Write(cbMinOnStart->Checked);

				 bw->Write(cbAskQuit->Checked);

				 bw->Write(Convert::ToInt32(numericFilterStep->Value));
				 bw->Write(Convert::ToInt32(numericRitXit->Value));

				 bw->Write( Convert::ToInt32(trackAccel0->Value) );
				 bw->Write( Convert::ToInt32(trackAccel1->Value) );
				 bw->Write( Convert::ToInt32(trackAccel2->Value) );
				 bw->Write( Convert::ToInt32(trackAccel3->Value) );
				 bw->Write( Convert::ToInt32(trackAccel4->Value) );
				 bw->Write( Convert::ToInt32(trackAccel5->Value) );

				 bw->Write(tbF_first->Text);
				 bw->Write(tbF_second->Text);

				 bw->Write(PuPoProvider.Acceleration);
				 bw->Write(cbUseFreqAcc->Checked);

				 bw->Write(cbSmMatrix->Text);

				 bw->Close();

			 }
			 catch (...)
			 {
				 MessageBox::Show("Íå óäàëîñü ñîõðàíèòü íàñòðîéêè");
			 }
		 }
private: void ReadSettings(void){

			 FileStream^ f_stream;
			 BinaryReader^ br;

			 try
			 {
				 f_stream = gcnew FileStream(System::IO::Path::GetDirectoryName(System::Windows::Forms::Application::ExecutablePath)+"\\settings.cfg", FileMode::Open);
				 br = gcnew BinaryReader(f_stream);
			 }
			 catch (...)
			 {
				 return;
			 };

			 try
			 {
				 cbPortName->Text			= br->ReadString();
				 com0comPair				= br->ReadInt32();
				 cbAutostart->Checked		= br->ReadBoolean();
				 cbManualConnect->Checked	= br->ReadBoolean();
				 cbMinToTray->Checked		= br->ReadBoolean();
				 cbMinOnStart->Checked		= br->ReadBoolean();

				 cbAskQuit->Checked			= br->ReadBoolean();

				 numericFilterStep->Value	= br->ReadInt32();
				 numericRitXit->Value		= br->ReadInt32();

				 trackAccel0->Value			= br->ReadInt32();
				 trackAccel1->Value			= br->ReadInt32();
				 trackAccel2->Value			= br->ReadInt32();
				 trackAccel3->Value			= br->ReadInt32();
				 trackAccel4->Value			= br->ReadInt32();
				 trackAccel5->Value			= br->ReadInt32();

				 tbF_first->Text			= br->ReadString();
				 tbF_second->Text			= br->ReadString();

				 PuPoProvider.Acceleration  = br->ReadBoolean();
				 cbUseFreqAcc->Checked		= br->ReadBoolean();
				 cbUseFreqAcc_CheckedChanged(this, gcnew EventArgs());

				 cbSmMatrix->Text			= br->ReadString();
			 }
			 catch (...)
			 {
			 }

			 br->Close();
		 }

private: System::Void cbAutostart_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 System::String^ name = "TuneSDRcom";
			 System::String^ ExePath = System::Windows::Forms::Application::ExecutablePath;
			 Microsoft::Win32::RegistryKey^ reg;
			 reg = Microsoft::Win32::Registry::CurrentUser->CreateSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Run\\");

			 if (cbAutostart->Checked)
			 {
				 try
				 {               
					 reg->SetValue(name, ExePath);
					 reg->Close();

				 }
				 catch (...) { cbAutostart->Enabled=false; }
			 } 
			 else
			 {
				 try
				 {               
					 reg->DeleteValue(name);
					 reg->Close();

				 }
				 catch (...) { cbAutostart->Enabled=false; }
			 }
		 }
#pragma endregion

#pragma region ²í³ö³àë³çàö³ÿ
private: Void this_Load(Object^ sender, EventArgs ^e) {
			label2->Text = "Ïîäêëþ÷èòå PowerSDR ê ïîðòó:      "+POWERSDR_OUT_PORT+"          Baud Rate: 19200";
			serialPSDR->PortName = POWERSDR_IN_PORT;

			 CloseWithoutAsking=false;

			 PuPoProvider.PoPuPro = %PoPuProvider;
			 
			 bool onlyInstance;
			 System::Threading::Mutex^ mtx = gcnew System::Threading::Mutex(true, "TuneSDR.com", onlyInstance);
			 if (!onlyInstance)
			 {
				 CloseWithoutAsking=true;
				 this->Close();
			 }


			ForEachControlPair(Init())

				MinimizeOnLaunch=true;

			pinMap = gcnew PinMap;
			pairs = gcnew PortPairs(this);

			pairs->Init();
			Reset();
			if(!InitialCom0ComSetup())
			{
				MessageBox::Show("Ïðè èíèöèàëèçàöèè ïðîãðàììû ïðîèçîøåë ñáîé.\r\n Ïîïðîáóéòå ïåðåçàïóñòèòü ïðîãðàììó ñ ïðàâàìè àäìèíèñòðàòîðà.");
			}

			array<Object^>^ objectArray = this->serialPSDR->GetPortNames();
			cbPortName->Items->AddRange(objectArray);
			cbPortName->Items->Remove(POWERSDR_IN_PORT);
			cbPortName->Items->Remove(POWERSDR_OUT_PORT);

			sm_paths.AddRange(Directory::GetFiles(System::IO::Path::GetDirectoryName(Application::ExecutablePath)+"\\SM", "*.tsm"));

			for each (String^ path in sm_paths)
			{
				cbSmMatrix->Items->Add(/*(*/System::IO::Path::GetFileNameWithoutExtension(path)/*)->Replace("_"," ")*/);
			}

			ReadSettings();

			if (MinimizeOnLaunch && cbMinOnStart->Checked)
			{
				this->WindowState = FormWindowState::Minimized;
				//Form1_Resize(sender,e);
			}

			PuPoProvider.PoBtnSt=%PowerBtnStates;
			PoPuProvider.PoBtnSt=%PowerBtnStates;

			PuPoProvider.Acc0	=trackAccel0;
			PuPoProvider.Acc1	=trackAccel1;
			PuPoProvider.Acc2	=trackAccel2;
			PuPoProvider.Acc3	=trackAccel3;
			PuPoProvider.Acc4	=trackAccel4;
			PuPoProvider.Acc5	=trackAccel5;

			PuPoProvider.NumFilt	= numericFilterStep;
			PuPoProvider.NumRitXit	= numericRitXit;

			PuPoProvider.tbFFirst	= tbF_first;
			PuPoProvider.tbFSecond	= tbF_second;

			timerOpenPorts->Enabled = true;
			timerReadRC->Enabled	= true;
			timerReadPSDR->Enabled	= true;
			timerPsdrAsker->Enabled	= true;
			timerPTT->Enabled		= true;

			trackAccel0_Scroll(sender,e);
			trackAccel1_Scroll(sender,e);
			trackAccel2_Scroll(sender,e);
			trackAccel3_Scroll(sender,e);
			trackAccel4_Scroll(sender,e);
			trackAccel5_Scroll(sender,e);

			
			
}

private: bool InitialCom0ComSetup(){
					  if (!SaveChanges())
						  return false;

					  if (checkListForOurPorts(POWERSDR_IN_PORT,POWERSDR_OUT_PORT))
					  {
						  notifyIcon->BalloonTipText = "TuneSDR.com çàïóùåí â òðåå";
						  notifyIcon->ShowBalloonTip(1000);
						  return true;
					  }

					  notifyIcon->BalloonTipText = "Ïðîèçâîæó íàñòðîéêó âèðòóàëüíûõ ïðîòîâ.\nÝòî ìîæåò çàíÿòü íåñêîëüêî ìèíóò, ïîæàëóéñòà æäèòå.";
					  notifyIcon->ShowBalloonTip(1000);

					  this->WindowState = FormWindowState::Minimized;

					  String ^key;
					  try {key = pairs->AddPair();} catch(...){return false;};
					  com0comPair=Convert::ToInt32(key);

					  //MessageBox::Show(key);
					  MinimizeOnLaunch=false;
					  
					  ShowSettings();

					  Reset();

					  try {
						  pairList->SelectedNode = pairList->Nodes[key];
					  }
					  catch (Exception^ /*e*/) {
						  return false;
					  }

					  try
					  {
						  PortNameA->Text	=	POWERSDR_IN_PORT;
						  PortNameB->Text	=	POWERSDR_OUT_PORT;
						  //EmuBrA->Checked=true;
						  // 				EmuBrB->Checked=true;
						  //HiddenModeA->Checked=true;
						  // 				HiddenModeB->Checked=true;
						  //ExclusiveModeA->Checked=true;
						  // 				ExclusiveModeB->Checked=true;

						  if (pairList->SelectedNode) {
							  pairs->ChangePair(pairList->SelectedNode->Name, GetChanges());
							  Reset();
						  }

						  notifyIcon->BalloonTipText = "Íàñòðîéêà óñïåøíî çàêîí÷åíà. ";
						  notifyIcon->ShowBalloonTip(1000);
					  }
					  catch (...)
					  {
						  notifyIcon->BalloonTipText = "Ïðîèçîøëà íåèçâåñòíàÿ îøèáêà :(";
						  notifyIcon->ShowBalloonTip(1000);
						  return false;
					  };


					  return true;
				  };

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
#pragma endregion

#pragma region òàéìåðè
private: System::Void timerOpenPorts_Tick(System::Object^  sender, System::EventArgs^  e) {
			 if (!serialPSDR->IsOpen)
			 {
				 serialPSDR->Close();
				 try{serialPSDR->Open(); toolStripTune->ForeColor = Color::Green; } catch (...){ toolStripTune->ForeColor = Color::Red; };
			 }

			 if (PSDR_isConnected)
			 {
				 toolStripPower->ForeColor=Color::Green;
			 }
			 else
			 {
				 if (serialPSDR->IsOpen)
				 {
					 toolStripPower->ForeColor = Color::Orange;
				 }
				 else
				 {
					 toolStripPower->ForeColor=Color::Red;
				 }
			 }
			 PSDR_isConnected=false;

			 if (serialPSDR->IsOpen)
			 {
				 try {serialPSDR->Write("ZZFA;");} catch(...){};
			 }

			 //ïóëüò
			 if (this->WindowState != FormWindowState::Normal || !cbManualConnect->Checked)
			 if (!serialRC->IsOpen || serialRC->PortName!=cbPortName->Text || !RC_isConnected)
			 {
				 serialRC->Close();
				 serialRC->PortName=cbPortName->Text;
				 try { serialRC->Open(); } catch (...){};
				 PoPuProvider.SendTime();
				 PoPuProvider.SendDate();
				 try { serialRC->Write(PoPuProvider.PowerAnswer,0,PoPuProvider.PowerAnswerIterator); } catch(...){};
				 PoPuProvider.PowerAnswerIterator=0;

			 }

			 if (RC_isConnected)
			 {
				 toolStripPult->ForeColor=Color::Green;
			 }
			 else
			 {
				 if (serialRC->IsOpen)
				 {
					 toolStripPult->ForeColor = Color::Orange;
				 }
				 else
				 {
					 toolStripPult->ForeColor=Color::Red;
				 }
			 }
			 RC_isConnected=false;

			 if (serialRC->IsOpen)
			 {
				 /*label1->Text = " ïîðò îòêðûò";*/
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
			 try { serialRC->Read(messages,0,BTR); } catch(...){};

			 if (PuPoProvider.ProvideCmd(messages[BTR-1]))
			 {
				 PoPuProvider.SetLED(PuPoProvider.modeBtn, PuPoProvider.pttBtn);
				 PoPuProvider.SendSmLed();
				 PoPuProvider.SendMdPAmpBtns();
			 }
			 else
			 {
//				 textBox1->Text = Convert::ToString(messages[BTR-1]) + "\r\n" + textBox1->Text;
				 return;
			 }
			 
			 try
			 {
			 	 serialPSDR->Write(PuPoProvider.PowersdrCmds->ToString()+"ZZFA;ZZFB;");
				 
			 }
			 catch (...){};
			 PuPoProvider.PowersdrCmds->Clear();

			 
		 }


private: System::Void timerReadPSDR_Tick(System::Object^  sender, System::EventArgs^  e) {
			 if (!serialPSDR->IsOpen) { return; }
			 if (serialPSDR->BytesToRead<1) { return; }

			 PSDR_isConnected = true;
			 System::String^ message;

			 try 
			 {
				 message=serialPSDR->ReadExisting();
			 } 
			 catch (...) 
			 {
				 return;
			 }
 
			 
 
 			 List<System::String^>^ anslist= gcnew List<System::String^>(message->Split(';'));
			 if (anslist != nullptr)
			 {
				 for each (System::String^ ans in anslist)
				 {
					 if(PoPuProvider.ProvideAnswer(ans))
					 {
						 try { serialRC->Write(PoPuProvider.PowerAnswer,0,PoPuProvider.PowerAnswerIterator); } catch(...){};
						 PoPuProvider.PowerAnswerIterator=0;
					 }
				 }
			 }
 			
// 			 if (serialPSDR->IsOpen)
// 			 {
// 				 try {serialPSDR->WriteLine("ZZFA;ZZFB;");} catch(...){};
// 			 }
		 }

private: System::Void timerPsdrAsker_Tick(System::Object^  sender, System::EventArgs^  e) {
			if (serialPSDR->IsOpen)
			{
				try 
				{
					serialPSDR->Write("ZZSM0;");
					serialPSDR->Write(PowerAsker.GetQuestion()); 
					//MessageBeep(1);
				} catch(...) {};
			}
		}
#pragma endregion

#pragma region Êíîïêà Ïîäêëþ÷èòü
private: System::Void buttonConnect_Click(System::Object^  sender, System::EventArgs^  e) {
			 serialRC->Close();
			 serialRC->PortName=cbPortName->Text;
			 try{serialRC->Open();} catch (...){};
		 }
#pragma endregion

#pragma region Ïåðåä çàêðûòèåì ôîðìû
private: System::Void Form1_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
			 WriteSettings();

			 if (!CloseWithoutAsking && cbAskQuit->Checked) 
			 {
				 System::Windows::Forms::DialogResult diag_res = MessageBox::Show("Âû óâåðåíû ÷òî õîòèòå çàâåðøèòü ðàáîòó ïðèëîæåíèÿ TuneSDR.com?","Âûõîä?",MessageBoxButtons::OKCancel);

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
		 }
#pragma endregion

private: System::Void button1_Click_1(System::Object^  sender, System::EventArgs^  e) {
			 InitialCom0ComSetup();
		 }

#pragma region Èêîíêà â òðåå
private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) {
			 if (this->WindowState == FormWindowState::Minimized && cbMinToTray->Checked)
			 {
				 this->Hide();
				 this->ShowInTaskbar = false;
				 //notifyIcon->Visible = true;
			 }
		 }

private: System::Void notifyIcon_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 if (e->Button == System::Windows::Forms::MouseButtons::Left)
			 {
				 ShowSettings();
			 }
		 }

private: void ShowSettings(void){
			this->Show();
			this->WindowState = FormWindowState::Normal;
			this->ShowInTaskbar = true;
			this->TopMost=true;
			this->TopMost=false;
		 }

private: System::Void íàñòðîéêèToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 ShowSettings();
		 }
private: System::Void âûõîäToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->Close();
		 }
private: System::Void ñàéòÏðîåêòàToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 System::Diagnostics::Process::Start("http://www.tunesdr.com/");
		 }
#pragma endregion

#pragma region Óñêîðåíèå âàëêîäà
private: System::Void trackAccel0_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 labelAccel0->Text = AccelerationSteps[trackAccel0->Value];
		 }
private: System::Void trackAccel1_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 labelAccel1->Text = AccelerationSteps[trackAccel1->Value];
		 }
private: System::Void trackAccel2_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 labelAccel2->Text = AccelerationSteps[trackAccel2->Value];
		 }
private: System::Void trackAccel3_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 labelAccel3->Text = AccelerationSteps[trackAccel3->Value];
		 }
private: System::Void trackAccel4_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 labelAccel4->Text = AccelerationSteps[trackAccel4->Value];
		 }
private: System::Void trackAccel5_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 labelAccel5->Text = AccelerationSteps[trackAccel5->Value];
		 }
private: System::Void BtnAccelDefaults_Click(System::Object^  sender, System::EventArgs^  e) {
			 trackAccel0->Value = 0;
			 trackAccel1->Value = 1;
			 trackAccel2->Value = 1;
			 trackAccel3->Value = 2;
			 trackAccel4->Value = 3;
			 trackAccel5->Value = 4;
			 trackAccel0_Scroll(sender,e);
			 trackAccel1_Scroll(sender,e);
			 trackAccel2_Scroll(sender,e);
			 trackAccel3_Scroll(sender,e);
			 trackAccel4_Scroll(sender,e);
			 trackAccel5_Scroll(sender,e);
		 }
#pragma endregion

private: System::Void btnResetFilterStep_Click(System::Object^  sender, System::EventArgs^  e) {
			 numericFilterStep->Value = 100;
		 }
private: System::Void btnResetRitXit_Click(System::Object^  sender, System::EventArgs^  e) {
			 numericRitXit->Value = 100;
		 }
private: System::Void timerPTT_Tick(System::Object^  sender, System::EventArgs^  e) {
			 
			 if (pttOld != PuPoProvider.pttBtn)
			 {
				 if (PuPoProvider.pttBtn == 2)
				 {
					 PuPoProvider.PowersdrCmds->Append("ZZTX0;");
					 PoPuProvider.SendSmLed();
				 }
				 else if (PuPoProvider.pttBtn == 1)
				 {
					 PuPoProvider.PowersdrCmds->Append("ZZTX1;");
					 PoPuProvider.SendSmLed();
				 }
			 }
			 			
			 pttOld	=	PuPoProvider.pttBtn;
			 PuPoProvider.pttBtn=2;
		 }

private: System::Void cbUseFreqAcc_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 panelFreqAcc->Enabled	=	cbUseFreqAcc->Checked;
			 PuPoProvider.AccMode	=	cbUseFreqAcc->Checked;
		 }

private: System::Void cbPortName_Click(System::Object^  sender, System::EventArgs^  e) {
			 cbPortName->Items->Clear();
			 array<Object^>^ objectArray = this->serialPSDR->GetPortNames();
			 for (int i=0; i<objectArray->Length; i++)
			 {
				 if (objectArray[i]->ToString() != POWERSDR_IN_PORT && objectArray[i]->ToString() != POWERSDR_OUT_PORT)
				 {
					  cbPortName->Items->Add(objectArray[i]);
				 }
			 }

		 }
private: System::Void cbSmMatrix_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 StreamReader^ sr;

			 try { sr = File::OpenText(sm_paths[cbSmMatrix->SelectedIndex]); } catch (...) {return;}

			 try 
			 {

				for (int i=0; i<261; i++)
				{
					PoPuProvider.smMatrix[i]=Convert::ToByte(sr->ReadLine());
				}
				PoPuProvider.smMatrixActive=true;
			 }
			 catch (...)
			 {
				 MessageBox::Show("Íå óäàëîñü ïðî÷èòàòü ôàéë êîððåêöèè S-ìåòðà, ðåçåðâíûé ðåæèì áóäåò èñïîëüçîâàí.");
				 PoPuProvider.smMatrixActive=false;
			 }

			 sr->Close();
		 }
};
}
