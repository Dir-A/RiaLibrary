#include "../../lib/RxUI/Win32.h"
#include "../../lib/Rut/RxFS.h"
#include "../../lib/Rut/RxPath.h"
#include "../../lib/Rut/RxConsole.h"

using namespace Rut;
using namespace RxUI;


class DemoWindow : public Win32::Window::MainWindow
{
private:
	Win32::Font::Default m_fdFont;

	Win32::Widget::Editor m_wePath, m_weSize;
	Win32::Widget::Button m_wbSetPath, m_wbGetSize;

	Win32::Widget::GroupBox m_wRadioGroup;
	Win32::Widget::Radio m_wRadio1, m_wRadio2, m_wRadio3;

	Win32::Widget::GroupBox m_wCheckBoxGroup;
	Win32::Widget::CheckBox m_wCheckBox1, m_wCheckBox2, m_wCheckBox3;

	Win32::Widget::Editor_Multiline m_weTextBox;

	void ClickGetPath(HWND hWnd, WPARAM wParam)
	{
		m_weTextBox.AddNewLine(L"Call ClickGetPath");
		Win32::Dialog::OpenFile open_file_dialog;
		open_file_dialog.OpenDialog();
		for (auto& file_name : open_file_dialog.GetPathList())
		{
			m_weTextBox.AddNewLine(file_name);
		}

		std::wstring path = open_file_dialog.GetFirstPath();
		if (!path.empty())
		{
			m_wePath.SetText(path.data());
			m_wbGetSize.Enable(true);
		}
	}

	void EditorShowSize(HWND hWnd, WPARAM wParam)
	{
		m_weTextBox.AddNewLine(L"Call EditorShowSize");
		std::wstring path = m_wePath.GetText();
		if (!path.empty() && RxPath::FileExist(path))
		{
			wchar_t buf[100] = { 0 };
			wsprintfW(buf, L"0x%X Bytes", RxFS::Binary{ path, RIO::RIO_IN }.GetSize());
			m_weSize.SetText(buf);
		}
		else
		{
			m_weSize.SetText(L"路径错误!");
		}
	}

	void EditorEvent(HWND hWnd, WPARAM wParam)
	{
		m_weTextBox.AddNewLine(L"Call EditorEvent");
		if (HIWORD(wParam) == EN_SETFOCUS)
		{
			RxConsole::Put(L"EN_SETFOCUS\n");
		}
		else if (HIWORD(wParam) == EN_KILLFOCUS)
		{
			RxConsole::Put(L"EN_KILLFOCUS\n");
		}
	}

	void RadioEvent(HWND hWnd, WPARAM wParam)
	{
		m_weTextBox.AddNewLine(L"Call RadioEvent");
		if (hWnd == m_wRadio1.GetHandle())
		{
			RxConsole::Put(L"Radio_1_Checked\n");
			return;
		}

		if (hWnd == m_wRadio2.GetHandle())
		{
			RxConsole::Put(L"Radio_2_Checked\n");
			return;
		}

		if (hWnd == m_wRadio3.GetHandle())
		{
			RxConsole::Put(L"Radio_3_Checked\n");
			return;
		}

	}

	void CheckBoxEvent(HWND hWnd, WPARAM wParam)
	{
		m_weTextBox.AddNewLine(L"Call CheckBoxEvent");
		if (hWnd == m_wCheckBox1.GetHandle())
		{
			if (m_wCheckBox1.IsCheck())
			{
				RxConsole::Put(L"CheckBox_1_Checked\n");
			}
			else
			{
				RxConsole::Put(L"CheckBox_1_UnChecked\n");
			}
			return;
		}

		if (hWnd == m_wCheckBox2.GetHandle())
		{
			if (m_wCheckBox2.IsCheck())
			{
				RxConsole::Put(L"CheckBox_2_Checked\n");
			}
			else
			{
				RxConsole::Put(L"CheckBox_2_UnChecked\n");
			}
			return;
		}

		if (hWnd == m_wCheckBox3.GetHandle())
		{
			if (m_wCheckBox3.IsCheck())
			{
				RxConsole::Put(L"CheckBox_3_Checked\n");
			}
			else
			{
				RxConsole::Put(L"CheckBox_3_UnChecked\n");
			}
			return;
		}
	}

public:
	void InitRadioGroup(HWND hWnd, HFONT hFont)
	{
		{
			m_wRadio1.Create(L"Radio1", hWnd);
			m_wRadio1.NewGroup();
			m_wRadio1.SetFont(hFont);
			m_wRadio1.SetEvent(std::bind(&DemoWindow::RadioEvent, this, std::placeholders::_1, std::placeholders::_2));
			m_wRadio1.Run();

			m_wRadio2.Create(L"Radio2",hWnd);
			m_wRadio2.SetFont(hFont);
			m_wRadio2.SetEvent(std::bind(&DemoWindow::RadioEvent, this, std::placeholders::_1, std::placeholders::_2));
			m_wRadio2.Run();

			m_wRadio3.Create(L"Radio3",hWnd);
			m_wRadio3.SetFont(hFont);
			m_wRadio3.SetEvent(std::bind(&DemoWindow::RadioEvent, this, std::placeholders::_1, std::placeholders::_2));
			m_wRadio3.Run();
		}

		m_wRadioGroup.Create(L"RadioGroup",hWnd);
		m_wRadioGroup.NewGroup();
		m_wRadioGroup.SetFont(hFont);
		m_wRadioGroup.Run();
	}

	void InitCheckBoxGroup(HWND hWnd, HFONT hFont)
	{
		{
			m_wCheckBox1.Create(L"CheckBox1", hWnd);
			m_wCheckBox1.NewGroup();
			m_wCheckBox1.SetFont(hFont);
			m_wCheckBox1.SetEvent(std::bind(&DemoWindow::CheckBoxEvent, this, std::placeholders::_1, std::placeholders::_2));
			m_wCheckBox1.Run();

			m_wCheckBox2.Create(L"CheckBox2", hWnd);
			m_wCheckBox2.SetFont(hFont);
			m_wCheckBox2.SetEvent(std::bind(&DemoWindow::CheckBoxEvent, this, std::placeholders::_1, std::placeholders::_2));
			m_wCheckBox2.Run();

			m_wCheckBox3.Create(L"CheckBox3", hWnd);
			m_wCheckBox3.SetFont(hFont);
			m_wCheckBox3.SetEvent(std::bind(&DemoWindow::CheckBoxEvent, this, std::placeholders::_1, std::placeholders::_2));
			m_wCheckBox3.Run();
		}

		m_wCheckBoxGroup.Create(L"CheckBoxGroup", hWnd);
		m_wCheckBoxGroup.NewGroup();
		m_wCheckBoxGroup.SetFont(hFont);
		m_wCheckBoxGroup.Run();

	}

	void InitPathWdiget(HWND hWnd, HFONT hFont)
	{
		m_wePath.Create(L"请输入路径", hWnd);
		m_wePath.SetFont(hFont);
		m_wePath.SetEvent(std::bind(&DemoWindow::EditorEvent, this, std::placeholders::_1, std::placeholders::_2));
		m_wePath.Run();

		m_weSize.Create(L"获取大小", hWnd);
		m_weSize.SetFont(hFont);
		//m_Editor2.SetEventFunc(std::bind(&SubWindow::EditorEvent, this, std::placeholders::_1, std::placeholders::_2));
		m_weSize.Run();

		m_wbSetPath.Create(L"设置路径", hWnd);
		m_wbSetPath.SetFont(hFont);
		m_wbSetPath.SetEvent(std::bind(&DemoWindow::ClickGetPath, this, std::placeholders::_1, std::placeholders::_2));
		m_wbSetPath.Run();

		m_wbGetSize.Create(L"获取大小", hWnd);
		m_wbGetSize.SetFont(hFont);
		m_wbGetSize.SetEvent(std::bind(&DemoWindow::EditorShowSize, this, std::placeholders::_1, std::placeholders::_2));
		m_wbGetSize.Run();
		m_wbGetSize.Enable(false);
	}

public:
	DemoWindow()
	{

	}

	void OnCreate(WPARAM wParam, LPARAM lParam) override
	{
		HWND hwnd = this->GetHandle();

		m_fdFont.Create(L"微软雅黑", 18);

		m_weTextBox.Create(L"", hwnd);
		m_weTextBox.SetFont(m_fdFont.GetHandle());
		m_weTextBox.Run();

		InitRadioGroup(hwnd, m_fdFont.GetHandle());
		InitCheckBoxGroup(hwnd, m_fdFont.GetHandle());
		InitPathWdiget(hwnd, m_fdFont.GetHandle());
	}

	void OnSize(WPARAM wType, uint32_t uiWidth, uint32_t uiHeigh) override
	{
		m_wePath.SetRect(5, 05, uiWidth - 80, 25);
		m_weSize.SetRect(5, 35, uiWidth - 80, 25);
		m_wbSetPath.SetRect(uiWidth - 80 + 10, 03, 65, 30);
		m_wbGetSize.SetRect(uiWidth - 80 + 10, 33, 65, 30);

		uint32_t distance = (uint32_t)((float)uiWidth / 3.2);

		uint32_t radio_y = 70;
		{
			m_wRadio1.SetRect(30 + distance * 0, radio_y + 20, 100, 25);
			m_wRadio2.SetRect(30 + distance * 1, radio_y + 20, 100, 25);
			m_wRadio3.SetRect(30 + distance * 2, radio_y + 20, 100, 25);
			m_wRadioGroup.SetRect(5, radio_y, uiWidth - 10, 50);
		}

		uint32_t checkbox_y = 130;
		{
			m_wCheckBox1.SetRect(30 + distance * 0, checkbox_y + 20, 100, 25);
			m_wCheckBox2.SetRect(30 + distance * 1, checkbox_y + 20, 100, 25);
			m_wCheckBox3.SetRect(30 + distance * 2, checkbox_y + 20, 100, 25);
			m_wCheckBoxGroup.SetRect(5, 130, uiWidth - 10, 50);
		}

		m_weTextBox.SetRect(5, 190, uiWidth - 10, uiHeigh - 200);
	}
};

void DemoWndThread()
{
	DemoWindow demo_wnd;
	demo_wnd.Create(L"DemoClass", L"Demo");
	demo_wnd.SetCenter(500, 600);
	demo_wnd.Run();
	demo_wnd.Loop();
}

void TestRxUI()
{
	HANDLE demo_wnd_thread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)DemoWndThread, nullptr, 0, nullptr);
	if (demo_wnd_thread != nullptr)
	{
		WaitForSingleObject(demo_wnd_thread, INFINITE);
	}
}