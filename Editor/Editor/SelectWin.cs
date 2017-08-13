using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Editor
{
	public partial class SelectWin : Form
	{
		public SelectWin()
		{
			InitializeComponent();
		}
		private void OKBtn_Click(object sender, EventArgs e)
		{
			this.Close();
		}

		public int Perform(string title, string defaultValue, string[] itemList) // ret: -1 == cancelled
		{
			this.Text = title;

			if (itemList.Length == 0)
				itemList = new string[] { "(ERROR:NO-ITEMS)" };

			{
				ComboBox cb = this.CB選択項目;

				cb.Items.Clear();

				foreach (string item in itemList)
				{
					cb.Items.Add(item);
				}
				cb.MaxDropDownItems = cb.Items.Count;
				cb.Text = defaultValue;

				if (cb.SelectedIndex == -1)
					cb.SelectedIndex = 0;
			}

			this.ShowDialog();

			return this.CB選択項目.SelectedIndex;
		}
		public int Perform(string title, int defaultValue, int minval, int maxval, string itemPrefix, string itemSuffix)
		{
			List<string> itemList = new List<string>();

			for (int value = minval; value <= maxval; value++)
			{
				itemList.Add(itemPrefix + value + itemSuffix);
			}
			return minval + this.Perform(title, itemList[defaultValue - minval], itemList.ToArray());
		}
		public int Perform(string title, int defaultValue, int minval, int maxval)
		{
			return this.Perform(title, defaultValue, minval, maxval, "", "");
		}
	}
}
