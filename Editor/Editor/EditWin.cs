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
	public partial class EditWin : Form
	{
		private enum ShColumn
		{
			NUMBER,
			VALUE,
			PROMPT,
		}

		private FieldCellData TargetEnemy;

		public EditWin(FieldCellData targetEnemy)
		{
			this.TargetEnemy = targetEnemy;

			InitializeComponent();

			this.Text = "[ " + DC.I.EnemyList[this.TargetEnemy.Index].Name + " ]";

			this.EnemyPicBox.Image = DC.I.EnemyList[this.TargetEnemy.Index].Mitame.ImageData;
			this.EnemyPicBox.BackColor = Color.Black;

			this.InitSheet(this.CPVSheet, DC.I.EnemyCommonParamPromptList, this.TargetEnemy.CommonParamValueList);
			this.InitSheet(this.PVSheet, DC.I.EnemyList[this.TargetEnemy.Index].ParamPromptList, this.TargetEnemy.ParamValueList);
		}
		private void InitSheet(DataGridView sheet, ResourceDataList prompts, ResourceDataList values)
		{
			Tools.InitTileSheet(sheet);

			sheet.AllowUserToResizeColumns = true;
			sheet.ColumnHeadersVisible = true;
			sheet.RowTemplate.Height = 20;

			try
			{
				sheet.Font = new Font("MS Gothic", 10f, FontStyle.Regular);
				//sheet.Font = new Font(Tools.GetUIFontName(), 10f, FontStyle.Regular);
			}
			catch
			{ }

			sheet.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
			sheet.MultiSelect = false;
			sheet.ReadOnly = true;

			sheet.RowCount = 0;
			sheet.ColumnCount = 0;

			sheet.Columns.Add(new DataGridViewTextBoxColumn());
			sheet.Columns.Add(new DataGridViewTextBoxColumn());
			sheet.Columns.Add(new DataGridViewTextBoxColumn());

			sheet.Columns[(int)ShColumn.NUMBER].HeaderText = "#";
			sheet.Columns[(int)ShColumn.VALUE].HeaderText = "値";
			sheet.Columns[(int)ShColumn.PROMPT].HeaderText = "値の説明";

			foreach (string r_prompt in prompts.GetValueList())
			{
				string prompt = r_prompt;

				if (prompt == ResourceData.DEFAULT_VALUE)
				{
					prompt = "(項目はありません)";
				}
				sheet.Rows.Add();

				DataGridViewRow row = sheet.Rows[sheet.Rows.Count - 1];
				int rowidx = sheet.Rows.Count - 1;

				row.Cells[(int)ShColumn.NUMBER].Value = "" + (rowidx + 1);
				row.Cells[(int)ShColumn.VALUE].Value = values.GetValue(rowidx);
				row.Cells[(int)ShColumn.PROMPT].Value = prompt;

				row.Cells[(int)ShColumn.NUMBER].Style.BackColor = Color.White;
				row.Cells[(int)ShColumn.VALUE].Style.BackColor = Color.LightYellow;
				row.Cells[(int)ShColumn.PROMPT].Style.BackColor = Color.White;
			}
			//sheet.Columns[(int)ShColumn.NUMBER].ReadOnly = true;
			//sheet.Columns[(int)ShColumn.VALUE].ReadOnly = false;
			//sheet.Columns[(int)ShColumn.PROMPT].ReadOnly = true;

			sheet.Columns[(int)ShColumn.NUMBER].Width = 30;
			sheet.Columns[(int)ShColumn.VALUE].Width = 100;
			sheet.Columns[(int)ShColumn.PROMPT].Width = 250;

			foreach (DataGridViewColumn column in sheet.Columns)
			{
				column.SortMode = DataGridViewColumnSortMode.NotSortable;
			}
			sheet.ClearSelection();
		}

		private void LSplit_SplitterMoved(object sender, SplitterEventArgs e)
		{
			this.RSplit.SplitterDistance = this.LSplit.SplitterDistance;
		}
		private void RSplit_SplitterMoved(object sender, SplitterEventArgs e)
		{
			this.LSplit.SplitterDistance = this.RSplit.SplitterDistance;
		}

		private bool WinActive;

		private void EditWin_Activated(object sender, EventArgs e)
		{
			if (this.WinActive)
				return;

			this.ActivateSheet(this.CPVSheet);
			this.ActivateSheet(this.PVSheet);

			this.PVSheet.Focus();

			this.WinActive = true;
		}
		private void ActivateSheet(DataGridView sheet)
		{
			sheet.ClearSelection();
		}

		private void EditWin_FormClosed(object sender, FormClosedEventArgs e)
		{
			this.CPVSheet.EndEdit();
			this.PVSheet.EndEdit();

			this.SaveSheet(this.CPVSheet, this.TargetEnemy.CommonParamValueList);
			this.SaveSheet(this.PVSheet, this.TargetEnemy.ParamValueList);
		}
		private void SaveSheet(DataGridView sheet, ResourceDataList dest)
		{
			for (int rowidx = 0; rowidx < sheet.Rows.Count; rowidx++)
			{
				dest.SetValue(rowidx, "" + sheet.Rows[rowidx].Cells[(int)ShColumn.VALUE].Value);
			}
		}

		private void EnemyPicBox_Click(object sender, EventArgs e)
		{
			this.LBPanel_Click(null, null);
		}
		private void LBPanel_Click(object sender, EventArgs e)
		{
			try
			{
				this.CPVSheet.ClearSelection();
				this.PVSheet.ClearSelection();
			}
			catch
			{ }
		}

		private int GetSelectedRowIndex(DataGridView sheet)
		{
			for (int rowidx = 0; rowidx < sheet.RowCount; rowidx++)
			{
				if (sheet.Rows[rowidx].Selected)
				{
					return rowidx;
				}
			}
			return -1; // not found
		}
		private void EditValue(DataGridView sheet)
		{
			try
			{
				int rowidx = this.GetSelectedRowIndex(sheet);

				if(rowidx == -1)
					return;

				LineInputWin liw = new LineInputWin(
					"" + sheet.Rows[rowidx].Cells[(int)ShColumn.VALUE].Value,
					"" + sheet.Rows[rowidx].Cells[(int)ShColumn.PROMPT].Value
					);

				liw.ShowDialog();
				sheet.Rows[rowidx].Cells[(int)ShColumn.VALUE].Value = "" + liw.ResultLine;
			}
			catch(Exception ex)
			{
				Tools.DispError(ex);
			}
		}
		private void CPVSheet_CellDoubleClick(object sender, DataGridViewCellEventArgs e)
		{
			this.EditValue(this.CPVSheet);
		}
		private void PVSheet_CellDoubleClick(object sender, DataGridViewCellEventArgs e)
		{
			this.EditValue(this.PVSheet);
		}
		private void CPVSheet_KeyDown(object sender, KeyEventArgs e)
		{
			if (e.KeyCode == Keys.Enter)
			{
				this.EditValue(this.CPVSheet);
				e.Handled = true;
			}
		}
		private void PVSheet_KeyDown(object sender, KeyEventArgs e)
		{
			if (e.KeyCode == Keys.Enter)
			{
				this.EditValue(this.PVSheet);
				e.Handled = true;
			}
		}
	}
}
