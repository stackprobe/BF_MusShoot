using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Diagnostics;

namespace BootMenu
{
	public partial class MainWin : Form
	{
		public MainWin()
		{
			InitializeComponent();
		}

		private void MainWin_Load(object sender, EventArgs e)
		{
			this.CBDataName.Items.Clear();

			for (int c = 0; c <= 30; c++)
			{
				this.CBDataName.Items.Add("" + c);
			}
			this.CBDataName.SelectedIndex = 0;
			this.CBDataName.MaxDropDownItems = this.CBDataName.Items.Count;
		}

		const string SAVE_DIR = "C:\\appdata\\HakoIIIStageData";
		private static string DATA_DIR
		{
			get
			{
#if false
				if (File.Exists("out\\Hako3.exe"))
					return "out";
				else
					return "EditorData";
#else
				return "EditorData";
#endif
			}
		}
		const string BACK_DATA_FILE = "StageData.txt";
		const string FRONT_DATA_FILE = "WallData.txt";

		private string GetSaveDataFile(int fileno, string ext)
		{
			return fileno.ToString("0000") + ext;
		}
		private string GetSaveBackDataFile(int fileno)
		{
			return this.GetSaveDataFile(fileno, ".wall");
		}
		private string GetSaveFrontDataFile(int fileno)
		{
			return this.GetSaveDataFile(fileno, ".front");
		}

		private void OKButton_Click(object sender, EventArgs e)
		{
			try
			{
				if (Directory.Exists(SAVE_DIR) == false)
					Directory.CreateDirectory(SAVE_DIR);

				if (Directory.Exists(DATA_DIR) == false)
					throw new Exception();

				int fileno = int.Parse(this.CBDataName.Text);

				string sbFile = Path.Combine(SAVE_DIR, this.GetSaveBackDataFile(fileno));
				string sfFile = Path.Combine(SAVE_DIR, this.GetSaveFrontDataFile(fileno));
				string dbFile = Path.Combine(DATA_DIR, BACK_DATA_FILE);
				string dfFile = Path.Combine(DATA_DIR, FRONT_DATA_FILE);

				if (File.Exists(sbFile) && File.Exists(sfFile))
				{
					File.Copy(sbFile, dbFile, true);
					File.Copy(sfFile, dfFile, true);
				}
				else
				{
					if (this.無きゃ削除.Checked)
					{
						File.WriteAllBytes(dbFile, new byte[] { });
						File.WriteAllBytes(dfFile, new byte[] { });
					}
				}

				this.Visible = false;
				try
				{
					ProcessStartInfo psi = new ProcessStartInfo();

					psi.WorkingDirectory = "Editor\\Editor\\bin\\Release";
					psi.FileName = "Editor.exe";

					Process.Start(psi).WaitForExit();
				}
				finally
				{
					this.Visible = true;
					this.TMCount = 6;
				}

				File.Copy(dbFile, sbFile, true);
				File.Copy(dfFile, sfFile, true);
			}
			catch (Exception ex)
			{
				MessageBox.Show(
					"" + ex.Message,
					"" + ex,
					MessageBoxButtons.OK,
					MessageBoxIcon.Error
					);
			}
		}

		private int TMCount;

		private void MainTimer_Tick(object sender, EventArgs e)
		{
			if (0 < this.TMCount)
			{
				this.TopMost = this.TMCount % 2 == 0; // 最後はfalse
				this.TMCount--;
			}
		}
	}
}
