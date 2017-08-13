using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Reflection;
using System.IO;
using System.Runtime.InteropServices;
using System.Drawing;

namespace Editor
{
	public class CtrlException : Exception
	{
		public CtrlException()
			: base()
		{ }

		public CtrlException(string message)
			: base(message)
		{ }
	}

	public class UISuspend : IDisposable
	{
		private const uint IMF_DUALFONT = 0x80;
		private const uint WM_USER = 0x400;
		private const uint EM_SETLANGOPTIONS = (WM_USER + 120);
		private const uint EM_GETLANGOPTIONS = (WM_USER + 121);

		[DllImport("user32.dll", EntryPoint = "SendMessageA")]
		private static extern uint SendMessage(IntPtr hWnd, uint wMsg, uint wParam, uint lParam);

		private const Int32 WM_SETREDRAW = 0x000B;

		private static void SetWindowRedraw(IWin32Window window, bool fRedraw)
		{
			if ((window != null) && (window.Handle != IntPtr.Zero))
			{
				SendMessage(window.Handle, (uint)WM_SETREDRAW, (fRedraw) ? 1u : 0u, 0u);
			}
		}

		private Control Ctrl;

		public UISuspend(Control ctrl)
		{
			SetWindowRedraw(ctrl, false);
			this.Ctrl = ctrl;
		}

		public void Dispose()
		{
			if (this.Ctrl != null)
			{
				SetWindowRedraw(this.Ctrl, true);
				this.Ctrl.Refresh();
				this.Ctrl = null;
			}
		}
	}

	public class Tools
	{
		private static string _UIFontName = null;

		public static string GetUIFontName()
		{
			if (_UIFontName == null)
			{
				string name = "メイリオ";

				if (Tools.CheckFontName(name) == false)
				{
					name = "MS UI Gothic";
				}
				_UIFontName = name;
			}
			return _UIFontName;
		}
		private static bool CheckFontName(string name)
		{
			try
			{
				if (new Font(name, 10f, FontStyle.Regular).Name == name)
				{
					return true;
				}
			}
			catch
			{ }

			return false;
		}

		public static int ParseInt(string str, int defaultValue, int minval, int maxval)
		{
			int value = Tools.ParseInt(str, defaultValue);

			value = Math.Max(value, minval);
			value = Math.Min(value, maxval);

			return value;
		}
		public static int ParseInt(string str, int defaultValue)
		{
			try
			{
				return int.Parse(str.Trim());
			}
			catch
			{ }

			return defaultValue;
		}
		public static int ParseInt(string str)
		{
			return Tools.ParseInt(str, -1);
		}

		public static void AddToValues<T>(List<T> dest, List<T> src)
		{
			foreach (T srcval in src)
			{
				dest.Add(srcval);
			}
		}
		public static void RTrim(List<string> lines)
		{
			while (0 < lines.Count && lines[lines.Count - 1] == "")
			{
				lines.RemoveAt(lines.Count - 1);
			}
		}

		public static Encoding CP932 = Encoding.GetEncoding(932);

		public static FileStream FOpenR(string file)
		{
			return new FileStream(file, FileMode.Open, FileAccess.Read);
		}
		public static FileStream FOpenW(string file)
		{
			return new FileStream(file, FileMode.Create, FileAccess.Write);
		}
		public static StreamReader FOpenRT(string file, Encoding enc)
		{
			return new StreamReader(Tools.FOpenR(file), enc);
		}
		public static StreamWriter FOpenWT(string file, Encoding enc)
		{
			return new StreamWriter(Tools.FOpenW(file), enc);
		}

		public static void InitTileSheet(DataGridView sheet)
		{
			DoubleBufferOn(sheet);

			sheet.ReadOnly = true;
			sheet.AllowUserToAddRows = false;
			sheet.AllowUserToDeleteRows = false;
			sheet.AllowUserToResizeRows = false;
			sheet.AllowUserToResizeColumns = false;
			sheet.RowTemplate.Height = Consts.TILE_H;
			sheet.RowHeadersVisible = false;
			sheet.ColumnHeadersVisible = false;
		}
		public static void DoubleBufferOn(Control ctrl)
		{
			typeof(Control).GetProperty(
				"DoubleBuffered",
				BindingFlags.Instance | BindingFlags.NonPublic
				)
				.SetValue(ctrl, true, null);
		}
		public static void ResizeTileSheet(DataGridView sheet, int rowcnt, int colcnt)
		{
			sheet.RowCount = 0;
			sheet.ColumnCount = 0;

			for (int colidx = 0; colidx < colcnt; colidx++)
			{
				DataGridViewImageColumn column = new DataGridViewImageColumn();

				column.Width = Consts.TILE_W;
				column.Image = DC.I.DefaultTile.NormalImage.ImageData;

				sheet.Columns.Add(column);
			}
			sheet.RowCount = rowcnt;
		}

		public static void DispError(string message, string title)
		{
			MessageBox.Show(message, title, MessageBoxButtons.OK, MessageBoxIcon.Error);
		}
		public static void DispError(Exception e, string title)
		{
			Tools.DispError("" + e, title);
		}
		public static void DispError(Exception e)
		{
			Tools.DispError(e, "" + e.Message);
		}

		public static int[] GetSelectPos(DataGridView sheet)
		{
			for (int x = 0; x < sheet.ColumnCount; x++)
			{
				for (int y = 0; y < sheet.RowCount; y++)
				{
					if (sheet[x, y].Selected)
					{
						return new int[] { x, y };
					}
				}
			}
			return null; // not found
		}
		public static int[] GetSelectSize(DataGridView sheet, int[] pos)
		{
			int xPos = pos[0];
			int yPos = pos[1];

			int x;
			int y;

			for (x = 1; xPos + x < sheet.ColumnCount; x++)
			{
				if (sheet[xPos + x, yPos].Selected == false)
				{
					break;
				}
			}
			for (y = 1; yPos + y < sheet.RowCount; y++)
			{
				if (sheet[xPos, yPos + y].Selected == false)
				{
					break;
				}
			}
			return new int[] { x, y };
		}
		public static void SelectRect(DataGridView sheet, int[] pos, int[] size)
		{
			int l = pos[0];
			int t = pos[1];
			int w = size[0];
			int h = size[1];

			sheet.ClearSelection();

			for (int x = 0; x < w; x++)
			{
				for (int y = 0; y < h; y++)
				{
					sheet[l + x, t + y].Selected = true;
				}
			}
		}

		public static int GetSelectRowIndex(DataGridView sheet)
		{
			for (int index = 0; index < sheet.RowCount; index++)
			{
				if (sheet.Rows[index].Selected)
				{
					return index;
				}
			}
			return -1; // not found
		}
	}
}
