using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;

namespace Editor
{
	public partial class MainWin : Form
	{
		public MainWin()
		{
			InitializeComponent();

			this.FieldSheet.MouseWheel += new MouseEventHandler(this.FSWheel);

			Tools.InitTileSheet(this.MapSheet);
			Tools.InitTileSheet(this.EnemySheet);
			Tools.InitTileSheet(this.FieldSheet);

			new BusyWin("起動中", "リソースを読み込んでいます...").Perform(this.Init);

			this.FieldScroll.Maximum = DC.I.FieldScrollMax;
			this.WindowState = FormWindowState.Maximized;

			this.UIUpdate();
		}
		public void Init()
		{
			DC.I.Init();
			this.LoadMapSheet();
			this.LoadEnemySheet();
			this.LoadFieldSheet();
		}

		public void LoadMapSheet()
		{
			MapTable mt = DC.I.MapTableList[DC.I.MapTableIndex];
			Tools.ResizeTileSheet(this.MapSheet, mt.Height, mt.Width);
			this.UpdateMapSheet();
		}
		public void UpdateMapSheet()
		{
			MapTable mt = DC.I.MapTableList[DC.I.MapTableIndex];

			for (int x = 0; x < mt.Width; x++)
			{
				for (int y = 0; y < mt.Height; y++)
				{
					TileImage tile = mt.Table[y][x].Tile;
					Image image;

					if(this.MapSheet[x, y].Selected)
						image = tile.SelectedImage.ImageData;
					else
						image = tile.NormalImage.ImageData;

					if (this.MapSheet[x, y].Value != image)
						this.MapSheet[x, y].Value = image;
				}
			}
		}

		public enum EnemySheetColumn
		{
			画像,
			名称,
		}
		public void LoadEnemySheet()
		{
			this.EnemySheet.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
			this.EnemySheet.MultiSelect = false;

			this.EnemySheet.RowCount = 0;
			this.EnemySheet.ColumnCount = 0;
			this.EnemySheet.Columns.Add(new DataGridViewImageColumn());
			this.EnemySheet.Columns.Add(new DataGridViewTextBoxColumn());
			this.EnemySheet.Columns[(int)EnemySheetColumn.画像].Width = Consts.TILE_W;
			this.EnemySheet.Columns[(int)EnemySheetColumn.名称].Width = 240;

			this.EnemySheet.RowCount = DC.I.EnemyList.Count;

			for (int index = 0; index < DC.I.EnemyList.Count; index++)
			{
				DataGridViewRow row = this.EnemySheet.Rows[index];
				Enemy e = DC.I.EnemyList[index];

				row.Cells[(int)EnemySheetColumn.画像].Value = e.Tile.NormalImage.ImageData;
				row.Cells[(int)EnemySheetColumn.名称].Value = e.Name;
			}
		}

		public void LoadFieldSheet()
		{
			Tools.ResizeTileSheet(this.FieldSheet, Consts.FIELDSHEET_H, Consts.FIELDSHEET_W);
			this.UpdateFieldSheet();
		}
		public void UpdateFieldSheet()
		{
			FieldTable fm = DC.I.FieldMap;

			for (int x = 0; x < Consts.FIELDSHEET_W; x++)
			{
				for (int y = 0; y < Consts.FIELDSHEET_H; y++)
				{
					FieldCell fc = fm.GetCell(x + DC.I.FieldSheetLeftXPos, y);
					FieldCellData fcd = null;

					if (DC.I.DispBackLayer && fc.BackCD != null)
					{
						fcd = fc.BackCD;
					}
					if (DC.I.DispFrontLayer && fc.FrontCD != null)
					{
						fcd = fc.FrontCD;
					}
					TileImage tile;

					if (fcd != null)
					{
						if (fcd.Index == Consts.ENEMY_INDEX_OF_WALL)
						{
							int[] mapPos = fcd.GetTilePos();

							int mapIndex = mapPos[0];
							int xPos = mapPos[1];
							int yPos = mapPos[2];

							try
							{
								tile = DC.I.MapTableList[mapIndex].Table[yPos][xPos].Tile;
							}
							catch
							{
								tile = DC.I.DefaultTile;
							}
						}
						else
							tile = DC.I.EnemyList[fcd.Index].Tile;
					}
					else
						tile = DC.I.DefaultTile;

					Image image;

					if (this.FieldSheet[x, y].Selected)
						image = tile.SelectedImage.ImageData;
					else
						image = tile.NormalImage.ImageData;

					if (this.FieldSheet[x, y].Value != image)
						this.FieldSheet[x, y].Value = image;
				}
			}
		}

		private bool ControlActive;
		private bool WinActive;

		private void MainWin_Activated(object sender, EventArgs e)
		{
			if (this.WinActive)
				return;

			this.ControlActive = true;
			this.WinActive = true;
		}
		private void MainWin_FormClosing(object sender, FormClosingEventArgs e)
		{
			this.ControlActive = false;
		}
		private void MainWin_FormClosed(object sender, FormClosedEventArgs e)
		{
			if(this.NoSaveQuitMode == false)
			{
				DC.I.SaveData();
			}
		}

		private bool ReqUpdateMapSheet;
		private bool ReqUpdateFieldSheet;
		private int SplitAdjustRemainCount = 30;
		private int MostTopCount;

		private void MainTimer_Tick(object sender, EventArgs e)
		{
			if (this.ControlActive == false)
				return;

			if (this.ReqUpdateMapSheet)
			{
				this.UpdateMapSheet();
				this.ReqUpdateMapSheet = false;
			}
			if (this.ReqUpdateFieldSheet)
			{
				this.UpdateFieldSheet();
				this.ReqUpdateFieldSheet = false;
			}

			if (0 < this.SplitAdjustRemainCount)
			{
				try
				{
					using (new UISuspend(this))
					{
						for (int c = 0; c < 100; c++)
						{
							if (this.FieldSheet.Controls[1].Visible) // ? 垂直スクロール表示
							{
								this.LeftSplit.SplitterDistance--;
							}
							else if (this.FieldSheet.Controls[0].Visible) // ? 水平スクロール表示
							{
								this.MainSplit.SplitterDistance += 10;

								if (this.FieldSheet.Controls[0].Visible == false)
								{
									this.LeftSplit.SplitterDistance += 100;
								}
							}
							else if(this.MapSheet.Controls[0].Visible)
							{
								this.MainSplit.SplitterDistance--;
							}
							else
							{
								this.MapSheet.ClearSelection();
								this.EnemySheet.ClearSelection();
								this.FieldSheet.ClearSelection();

								throw new Exception("done");
							}
						}
					}
					this.SplitAdjustRemainCount--;
				}
				catch
				{
					this.SplitAdjustRemainCount = 0;
				}
			}

			if (0 < this.MostTopCount)
			{
				this.MostTopCount--;
				this.TopMost = this.MostTopCount % 2 == 1;
			}
		}

		private void UIUpdate()
		{
			this.NV背景Layer.Checked = DC.I.DispBackLayer;
			//this.FldMnu背景Erase.Enabled = DC.I.DispBackLayer; // old

			this.NV敵Layer.Checked = DC.I.DispFrontLayer;
			//this.FldMnu敵Erase.Enabled = DC.I.DispFrontLayer; // old

			//this.FldMnuAllErase.Enabled = DC.I.DispBackLayer && DC.I.DispFrontLayer; // old

			this.NEdtLeftClickDeHaichi.Checked = DC.I.LeftClickDeHaichi;
			this.NVewNoDispGridLine.Checked = DC.I.NoDispGridLine;

			if (DC.I.NoDispGridLine)
				this.FieldSheet.CellBorderStyle = DataGridViewCellBorderStyle.None;
			else
				this.FieldSheet.CellBorderStyle = DataGridViewCellBorderStyle.Single;

			Color color_on = Color.LightSkyBlue;
			Color color_off = Color.DarkGray;

			this.SttF10.ForeColor = DC.I.LeftClickDeHaichi ? color_on : color_off;
			this.SttF11.ForeColor = DC.I.DispBackLayer ? color_on : color_off;
			this.SttF12.ForeColor = DC.I.DispFrontLayer ? color_on : color_off;
		}

		private void NV背景Layer_Click(object sender, EventArgs e)
		{
			DC.I.DispBackLayer = DC.I.DispBackLayer == false;

			this.UIUpdate();
			this.ReqUpdateFieldSheet = true;
		}
		private void NV敵Layer_Click(object sender, EventArgs e)
		{
			DC.I.DispFrontLayer = DC.I.DispFrontLayer == false;

			this.UIUpdate();
			this.ReqUpdateFieldSheet = true;
		}

		private void MapSheet_SelectionChanged(object sender, EventArgs e)
		{
			this.ReqUpdateMapSheet = true;
		}
		private void FieldSheet_SelectionChanged(object sender, EventArgs e)
		{
			this.ReqUpdateFieldSheet = true;
		}

		private void FldMnuSelectClear_Click(object sender, EventArgs e)
		{
			this.FieldSheet.ClearSelection();
		}

		private void FldMnu配置_Click(object sender, EventArgs e)
		{
			try
			{
				int[] destPos = Tools.GetSelectPos(this.FieldSheet);

				if (destPos == null)
					throw new CtrlException("フィールドマップの領域が選択されていません。");

				int[] destSize = Tools.GetSelectSize(this.FieldSheet, destPos);

				if (this.MainTabCtrl.SelectedIndex == 0) // ? Map
				{
					int[] srcPos = Tools.GetSelectPos(this.MapSheet);

					if (srcPos == null)
						throw new CtrlException("マップテーブルの領域が選択されていません。");

					int[] srcSize = Tools.GetSelectSize(this.MapSheet, srcPos);

					if (destSize[0] == 1 && destSize[1] == 1) // ? Single Cell Selected
					{
						for (int x = 0; x < this.MapSheet.ColumnCount; x++)
						{
							for (int y = 0; y < this.MapSheet.RowCount; y++)
							{
								if (this.MapSheet[x, y].Selected)
								{
									int rx = x - srcPos[0];
									int ry = y - srcPos[1];

									int dx = destPos[0] + rx;
									int dy = destPos[1] + ry;

									int mx = dx + DC.I.FieldSheetLeftXPos;
									int my = dy;

									if (
										0 <= mx &&
										0 <= my && my < Consts.FIELDMAP_H
										)
									{
										FieldCellData fcd = new FieldCellData(
											Consts.ENEMY_INDEX_OF_WALL,
											new ResourceDataList(),
											new ResourceDataList()
											);

										fcd.SetTilePos(
											DC.I.MapTableIndex,
											x,
											y
											);

										DC.I.FieldMap.GetCell(mx, my).BackCD = fcd;
									}
								}
							}
						}
					}
					else // ? Multi Cell Selected
					{
						for (int x = 0; x < destSize[0]; x++)
						{
							for (int y = 0; y < destSize[1]; y++)
							{
								FieldCellData fcd = new FieldCellData(
									Consts.ENEMY_INDEX_OF_WALL,
									new ResourceDataList(),
									new ResourceDataList()
									);

								fcd.SetTilePos(
									DC.I.MapTableIndex,
									srcPos[0] + x % srcSize[0],
									srcPos[1] + y % srcSize[1]
									);

								DC.I.FieldMap.GetCell(
									destPos[0] + x + DC.I.FieldSheetLeftXPos,
									destPos[1] + y
									)
									.BackCD = fcd;
							}
						}
						Tools.SelectRect(this.MapSheet, srcPos, srcSize);
					}
					Tools.SelectRect(this.FieldSheet, destPos, destSize);
				}
				else // ? Enemy
				{
					int enemyIndex = Tools.GetSelectRowIndex(this.EnemySheet);

					if (
						enemyIndex == -1 // not found
						//enemyIndex == Consts.ENEMY_INDEX_OF_WALL
						)
						throw new CtrlException("敵オブジェクトが選択されていないか、配置できない敵オブジェクトが選択されています。");

					for (int x = 0; x < this.FieldSheet.ColumnCount; x++)
					{
						for (int y = 0; y < this.FieldSheet.RowCount; y++)
						{
							if (this.FieldSheet[x, y].Selected)
							{
								FieldCellData fcd = DC.I.FieldMap.GetCell(x + DC.I.FieldSheetLeftXPos, y).FrontCD;

								if (fcd == null) // ? キャラなし
								{
									DC.I.FieldMap.GetCell(x + DC.I.FieldSheetLeftXPos, y).FrontCD = new FieldCellData(
										enemyIndex,
										new ResourceDataList(),
										new ResourceDataList()
										);
								}
							}
						}
					}
				}
				this.ReqUpdateFieldSheet = true;
			}
			catch (CtrlException ex)
			{
				Tools.DispError(ex.Message, "オブジェクト配置エラー");
			}
			catch (Exception ex)
			{
				Tools.DispError(ex);
			}
		}

		private bool NoSaveQuitMode;

		private void NAQuit_Click(object sender, EventArgs e)
		{
			this.Close();
		}
		private void NANoSaveQuit_Click(object sender, EventArgs e)
		{
			if (MessageBox.Show(
				"最後の保存からの変更を破棄して終了します。",
				"変更の破棄？",
				MessageBoxButtons.OKCancel,
				MessageBoxIcon.Warning,
				MessageBoxDefaultButton.Button2
				) == DialogResult.OK
				)
			{
				this.NoSaveQuitMode = true;
				this.Close();
			}
		}

		/*
		private void FldMnuAllErase_Click(object sender, EventArgs e)
		{
			this.FieldErase(false);
			this.FieldErase(true);
		}
		private void FldMnu背景Erase_Click(object sender, EventArgs e)
		{
			this.FieldErase(false);
		}
		private void FldMnu敵Erase_Click(object sender, EventArgs e)
		{
			this.FieldErase(true);
		}
		*/
		private void FldMnuErase_Click(object sender, EventArgs e)
		{
			if (DC.I.DispBackLayer)
			{
				this.FieldErase(false);
			}
			if (DC.I.DispFrontLayer)
			{
				this.FieldErase(true);
			}
		}
		private void FieldErase(bool frontMode)
		{
			for (int x = 0; x < this.FieldSheet.ColumnCount; x++)
			{
				for (int y = 0; y < this.FieldSheet.RowCount; y++)
				{
					if (this.FieldSheet[x, y].Selected)
					{
						int mx = x + DC.I.FieldSheetLeftXPos;
						int my = y;

						FieldCell fc = DC.I.FieldMap.Table[mx][my];

						if (frontMode)
							fc.FrontCD = null;
						else
							fc.BackCD = null;
					}
				}
			}
			this.ReqUpdateFieldSheet = true;
		}

		private void MapMnuSelectClear_Click(object sender, EventArgs e)
		{
			this.MapSheet.ClearSelection();
		}

		private void MapMnuマップ切り替え_Click(object sender, EventArgs e)
		{
			DC.I.MapTableIndex = new SelectWin().Perform(
				"マップを選択して下さい",
				DC.I.MapTableIndex,
				0,
				DC.I.MapTableList.Count - 1,
				"マップ [ ", " ]"
				);

			new BusyWin().Perform(DC.I.MapTableList[DC.I.MapTableIndex].Touch);

			this.ControlActive = false;
			this.LoadMapSheet();
			this.ControlActive = true;

			this.MapSheet.ClearSelection();
		}

		private void EneMnuSelectClear_Click(object sender, EventArgs e)
		{
			this.EnemySheet.ClearSelection();
		}

		private void FSWheel(object sender, MouseEventArgs e)
		{
			const int MOVE_SPAN = 20;

			try
			{
				int value = this.FieldScroll.Value;

				value -= MOVE_SPAN * Math.Sign(e.Delta);

				if (value < 0)
					value = 0;

				this.FieldScroll.Value = value;
				this.FSScrolled(value);
			}
			catch
			{ }
		}
		private void FieldScroll_Scroll(object sender, ScrollEventArgs e)
		{
			this.FSScrolled(e.NewValue);
		}
		private void FSScrolled(int pos)
		{
			DC.I.FieldSheetLeftXPos = pos;
			this.ReqUpdateFieldSheet = true;
		}

		private void FldMnuCopy_Click(object sender, EventArgs e)
		{
			try
			{
				int[] srcPos = Tools.GetSelectPos(this.FieldSheet);

				if (srcPos == null)
					throw new CtrlException("フィールドマップの領域が選択されていません。");

				int[] srcSize = Tools.GetSelectSize(this.FieldSheet, srcPos);

				DC.I.CT_W = srcSize[0];
				DC.I.CT_H = srcSize[1];
				DC.I.CopiedTable = new FieldCell[DC.I.CT_W][];

				int mx = srcPos[0] + DC.I.FieldSheetLeftXPos;
				int my = srcPos[1];

				for (int x = 0; x < DC.I.CT_W; x++)
				{
					DC.I.CopiedTable[x] = new FieldCell[DC.I.CT_H];

					for (int y = 0; y < DC.I.CT_H; y++)
					{
						DC.I.CopiedTable[x][y] = DC.I.FieldMap.Table[mx + x][my + y].GetClone();
					}
				}
				Tools.SelectRect(this.FieldSheet, srcPos, srcSize);

				return; // Successful
			}
			catch (CtrlException ex)
			{
				Tools.DispError(ex.Message, "コピー失敗");
			}
			catch (Exception ex)
			{
				Tools.DispError(ex);
			}

			DC.I.CT_W = 0;
			DC.I.CT_H = 0;
			DC.I.CopiedTable = null;
		}

		private void FldMnuPaste_Click(object sender, EventArgs e)
		{
			try
			{
				if (DC.I.CopiedTable == null)
					throw new CtrlException("コピー元がありません。");

				int[] destPos = Tools.GetSelectPos(this.FieldSheet);

				if (destPos == null)
					throw new CtrlException("フィールドマップの領域が選択されていません。");

				int[] destSize = Tools.GetSelectSize(this.FieldSheet, destPos);

				if (destSize[0] == 1 && destSize[1] == 1) // ? Single Cell Selected
				{
					for (int x = 0; x < DC.I.CT_W; x++)
					{
						for (int y = 0; y < DC.I.CT_H; y++)
						{
							int mx = destPos[0] + x + DC.I.FieldSheetLeftXPos;
							int my = destPos[1] + y;

							if (
								0 <= mx &&
								0 <= my && my < Consts.FIELDMAP_H
								)
							{
								FieldCell src_fc = DC.I.CopiedTable[x][y];
								FieldCell dest_fc = DC.I.FieldMap.Table[mx][my];

								if (DC.I.DispBackLayer)
								{
									dest_fc.BackCD = src_fc.BackCD;
								}
								if (DC.I.DispFrontLayer)
								{
									dest_fc.FrontCD = src_fc.FrontCD;
								}
							}
						}
					}
				}
				else // ? Multi Cell Selected
				{
					for (int x = 0; x < destSize[0]; x++)
					{
						for (int y = 0; y < destSize[1]; y++)
						{
							int sx = x % DC.I.CT_W;
							int sy = y % DC.I.CT_H;

							int dx = destPos[0] + x + DC.I.FieldSheetLeftXPos;
							int dy = destPos[1] + y;

							FieldCell src_fc = DC.I.CopiedTable[sx][sy];
							FieldCell dest_fc = DC.I.FieldMap.Table[dx][dy];

							if (DC.I.DispBackLayer)
							{
								dest_fc.BackCD = src_fc.BackCD;
							}
							if (DC.I.DispFrontLayer)
							{
								dest_fc.FrontCD = src_fc.FrontCD;
							}
						}
					}
				}
				Tools.SelectRect(this.FieldSheet, destPos, destSize);
			}
			catch (CtrlException ex)
			{
				Tools.DispError(ex.Message, "貼り付け失敗");
			}
			catch (Exception ex)
			{
				Tools.DispError(ex);
			}
		}

		private void FldMnuEdit_Click(object sender, EventArgs e)
		{
			try
			{
				int[] selPos = Tools.GetSelectPos(this.FieldSheet);

				if (selPos == null)
					throw new CtrlException("フィールドマップが選択されていません。");

				int selXPos = selPos[0] + DC.I.FieldSheetLeftXPos;
				int selYPos = selPos[1];

				FieldCellData fcd = DC.I.FieldMap.Table[selXPos][selYPos].FrontCD;

				if (fcd == null)
					throw new CtrlException("敵オブジェクトが選択されていません。");

				new EditWin(fcd).ShowDialog();
			}
			catch (CtrlException ex)
			{
				Tools.DispError(ex.Message, "編集失敗");
			}
			catch (Exception ex)
			{
				Tools.DispError(ex);
			}
		}

		private void NEdtLeftClickDeHaichi_Click(object sender, EventArgs e)
		{
			DC.I.LeftClickDeHaichi = DC.I.LeftClickDeHaichi == false;
			this.UIUpdate();
		}

		private void FieldSheet_Click(object sender, EventArgs e)
		{
			if (DC.I.LeftClickDeHaichi)
			{
				this.FldMnu配置_Click(null, null);
			}
		}

		private void NVewNoDispGridLine_Click(object sender, EventArgs e)
		{
			DC.I.NoDispGridLine = DC.I.NoDispGridLine == false;
			this.UIUpdate();
		}

		private void TestPlay(int startPos)
		{
			ProcessStartInfo psi = null;

			try
			{
				DC.I.SaveData();

				this.Visible = false;

				psi = new ProcessStartInfo();

				string WKDIR_1 = "..\\..\\..\\..\\out";
				string WKDIR_2 = "..\\..\\..\\..\\Shoot\\Release";

				if(File.Exists(Path.Combine(WKDIR_1, "Shoot.exe")))
					psi.WorkingDirectory = Path.GetFullPath(WKDIR_1);
				else
					psi.WorkingDirectory = Path.GetFullPath(WKDIR_2);

				psi.FileName = "Shoot.exe";
				psi.Arguments = "/TSP " + startPos;

				Process.Start(psi).WaitForExit();
			}
			catch (Exception e)
			{
				Tools.DispError(Directory.GetCurrentDirectory() + ", " + psi.WorkingDirectory + ", " + psi.FileName + ", " + e, e.Message);
			}
			finally
			{
				this.Visible = true;
				this.MostTopCount = 6;
			}
		}
		private void NTstFromTop_Click(object sender, EventArgs e)
		{
			this.TestPlay(0);
		}
		private void NTstFromSelect_Click(object sender, EventArgs e)
		{
			try
			{
				this.TestPlay(Tools.GetSelectPos(this.FieldSheet)[0] + DC.I.FieldSheetLeftXPos);
			}
			catch(Exception ex)
			{
				Tools.DispError(ex);
			}
		}

		private void FieldSheet_CellDoubleClick(object sender, DataGridViewCellEventArgs e)
		{
			this.FldMnuEdit_Click(null, null);
		}
	}
}
