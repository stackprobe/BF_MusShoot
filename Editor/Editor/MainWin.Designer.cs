namespace Editor
{
	partial class MainWin
	{
		/// <summary>
		/// 必要なデザイナ変数です。
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		/// <param name="disposing">マネージ リソースが破棄される場合 true、破棄されない場合は false です。</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows フォーム デザイナで生成されたコード

		/// <summary>
		/// デザイナ サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディタで変更しないでください。
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			this.MainSplit = new System.Windows.Forms.SplitContainer();
			this.LeftSplit = new System.Windows.Forms.SplitContainer();
			this.LTPanel = new System.Windows.Forms.Panel();
			this.SttF12 = new System.Windows.Forms.Label();
			this.SttF11 = new System.Windows.Forms.Label();
			this.SttF10 = new System.Windows.Forms.Label();
			this.FieldScroll = new System.Windows.Forms.HScrollBar();
			this.FieldSheet = new System.Windows.Forms.DataGridView();
			this.FieldMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.FldMnuSelectClear = new System.Windows.Forms.ToolStripMenuItem();
			this.FldMnu配置 = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripSeparator();
			this.FldMnuErase = new System.Windows.Forms.ToolStripMenuItem();
			this.FldMnuCopy = new System.Windows.Forms.ToolStripMenuItem();
			this.FldMnuPaste = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
			this.FldMnuEdit = new System.Windows.Forms.ToolStripMenuItem();
			this.MainTabCtrl = new System.Windows.Forms.TabControl();
			this.MapTabPage = new System.Windows.Forms.TabPage();
			this.MapSheet = new System.Windows.Forms.DataGridView();
			this.MapMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.MapMnuSelectClear = new System.Windows.Forms.ToolStripMenuItem();
			this.MapMnuマップ切り替え = new System.Windows.Forms.ToolStripMenuItem();
			this.EnemyTabPage = new System.Windows.Forms.TabPage();
			this.EnemySheet = new System.Windows.Forms.DataGridView();
			this.EnemyMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.EneMnuSelectClear = new System.Windows.Forms.ToolStripMenuItem();
			this.MainTimer = new System.Windows.Forms.Timer(this.components);
			this.North = new System.Windows.Forms.MenuStrip();
			this.NApp = new System.Windows.Forms.ToolStripMenuItem();
			this.NAQuit = new System.Windows.Forms.ToolStripMenuItem();
			this.NANoSaveQuit = new System.Windows.Forms.ToolStripMenuItem();
			this.NVew = new System.Windows.Forms.ToolStripMenuItem();
			this.NVLayer = new System.Windows.Forms.ToolStripMenuItem();
			this.NV背景Layer = new System.Windows.Forms.ToolStripMenuItem();
			this.NV敵Layer = new System.Windows.Forms.ToolStripMenuItem();
			this.NVewNoDispGridLine = new System.Windows.Forms.ToolStripMenuItem();
			this.NEdt = new System.Windows.Forms.ToolStripMenuItem();
			this.NEdtLeftClickDeHaichi = new System.Windows.Forms.ToolStripMenuItem();
			this.NTst = new System.Windows.Forms.ToolStripMenuItem();
			this.NTstFromTop = new System.Windows.Forms.ToolStripMenuItem();
			this.NTstFromSelect = new System.Windows.Forms.ToolStripMenuItem();
			this.MainSplit.Panel1.SuspendLayout();
			this.MainSplit.Panel2.SuspendLayout();
			this.MainSplit.SuspendLayout();
			this.LeftSplit.Panel1.SuspendLayout();
			this.LeftSplit.Panel2.SuspendLayout();
			this.LeftSplit.SuspendLayout();
			this.LTPanel.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.FieldSheet)).BeginInit();
			this.FieldMenu.SuspendLayout();
			this.MainTabCtrl.SuspendLayout();
			this.MapTabPage.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.MapSheet)).BeginInit();
			this.MapMenu.SuspendLayout();
			this.EnemyTabPage.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.EnemySheet)).BeginInit();
			this.EnemyMenu.SuspendLayout();
			this.North.SuspendLayout();
			this.SuspendLayout();
			// 
			// MainSplit
			// 
			this.MainSplit.Dock = System.Windows.Forms.DockStyle.Fill;
			this.MainSplit.Location = new System.Drawing.Point(0, 26);
			this.MainSplit.Name = "MainSplit";
			// 
			// MainSplit.Panel1
			// 
			this.MainSplit.Panel1.Controls.Add(this.LeftSplit);
			// 
			// MainSplit.Panel2
			// 
			this.MainSplit.Panel2.Controls.Add(this.MainTabCtrl);
			this.MainSplit.Size = new System.Drawing.Size(798, 480);
			this.MainSplit.SplitterDistance = 402;
			this.MainSplit.TabIndex = 0;
			// 
			// LeftSplit
			// 
			this.LeftSplit.Dock = System.Windows.Forms.DockStyle.Fill;
			this.LeftSplit.Location = new System.Drawing.Point(0, 0);
			this.LeftSplit.Name = "LeftSplit";
			this.LeftSplit.Orientation = System.Windows.Forms.Orientation.Horizontal;
			// 
			// LeftSplit.Panel1
			// 
			this.LeftSplit.Panel1.Controls.Add(this.LTPanel);
			// 
			// LeftSplit.Panel2
			// 
			this.LeftSplit.Panel2.Controls.Add(this.FieldScroll);
			this.LeftSplit.Panel2.Controls.Add(this.FieldSheet);
			this.LeftSplit.Size = new System.Drawing.Size(402, 480);
			this.LeftSplit.SplitterDistance = 304;
			this.LeftSplit.TabIndex = 0;
			// 
			// LTPanel
			// 
			this.LTPanel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.LTPanel.Controls.Add(this.SttF12);
			this.LTPanel.Controls.Add(this.SttF11);
			this.LTPanel.Controls.Add(this.SttF10);
			this.LTPanel.Location = new System.Drawing.Point(0, 0);
			this.LTPanel.Name = "LTPanel";
			this.LTPanel.Size = new System.Drawing.Size(402, 304);
			this.LTPanel.TabIndex = 0;
			// 
			// SttF12
			// 
			this.SttF12.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.SttF12.AutoSize = true;
			this.SttF12.Location = new System.Drawing.Point(94, 280);
			this.SttF12.Name = "SttF12";
			this.SttF12.Size = new System.Drawing.Size(30, 12);
			this.SttF12.TabIndex = 2;
			this.SttF12.Text = "◆EL";
			// 
			// SttF11
			// 
			this.SttF11.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.SttF11.AutoSize = true;
			this.SttF11.Location = new System.Drawing.Point(57, 280);
			this.SttF11.Name = "SttF11";
			this.SttF11.Size = new System.Drawing.Size(31, 12);
			this.SttF11.TabIndex = 1;
			this.SttF11.Text = "◆BL";
			// 
			// SttF10
			// 
			this.SttF10.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.SttF10.AutoSize = true;
			this.SttF10.Location = new System.Drawing.Point(20, 280);
			this.SttF10.Name = "SttF10";
			this.SttF10.Size = new System.Drawing.Size(31, 12);
			this.SttF10.TabIndex = 0;
			this.SttF10.Text = "◆LC";
			// 
			// FieldScroll
			// 
			this.FieldScroll.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this.FieldScroll.Location = new System.Drawing.Point(3, 150);
			this.FieldScroll.Name = "FieldScroll";
			this.FieldScroll.Size = new System.Drawing.Size(396, 18);
			this.FieldScroll.TabIndex = 1;
			this.FieldScroll.Scroll += new System.Windows.Forms.ScrollEventHandler(this.FieldScroll_Scroll);
			// 
			// FieldSheet
			// 
			this.FieldSheet.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
						| System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this.FieldSheet.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
			this.FieldSheet.ContextMenuStrip = this.FieldMenu;
			this.FieldSheet.Location = new System.Drawing.Point(3, 3);
			this.FieldSheet.Name = "FieldSheet";
			this.FieldSheet.RowTemplate.Height = 21;
			this.FieldSheet.Size = new System.Drawing.Size(396, 144);
			this.FieldSheet.TabIndex = 0;
			this.FieldSheet.CellDoubleClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.FieldSheet_CellDoubleClick);
			this.FieldSheet.SelectionChanged += new System.EventHandler(this.FieldSheet_SelectionChanged);
			this.FieldSheet.Click += new System.EventHandler(this.FieldSheet_Click);
			// 
			// FieldMenu
			// 
			this.FieldMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.FldMnuSelectClear,
            this.FldMnu配置,
            this.toolStripMenuItem2,
            this.FldMnuErase,
            this.FldMnuCopy,
            this.FldMnuPaste,
            this.toolStripMenuItem1,
            this.FldMnuEdit});
			this.FieldMenu.Name = "FieldMenu";
			this.FieldMenu.Size = new System.Drawing.Size(172, 148);
			// 
			// FldMnuSelectClear
			// 
			this.FldMnuSelectClear.Name = "FldMnuSelectClear";
			this.FldMnuSelectClear.Size = new System.Drawing.Size(171, 22);
			this.FldMnuSelectClear.Text = "選択クリア(&C)";
			this.FldMnuSelectClear.Click += new System.EventHandler(this.FldMnuSelectClear_Click);
			// 
			// FldMnu配置
			// 
			this.FldMnu配置.Name = "FldMnu配置";
			this.FldMnu配置.Size = new System.Drawing.Size(171, 22);
			this.FldMnu配置.Text = "配置(&H)";
			this.FldMnu配置.Click += new System.EventHandler(this.FldMnu配置_Click);
			// 
			// toolStripMenuItem2
			// 
			this.toolStripMenuItem2.Name = "toolStripMenuItem2";
			this.toolStripMenuItem2.Size = new System.Drawing.Size(168, 6);
			// 
			// FldMnuErase
			// 
			this.FldMnuErase.Name = "FldMnuErase";
			this.FldMnuErase.ShortcutKeys = System.Windows.Forms.Keys.Delete;
			this.FldMnuErase.Size = new System.Drawing.Size(171, 22);
			this.FldMnuErase.Text = "消去";
			this.FldMnuErase.Click += new System.EventHandler(this.FldMnuErase_Click);
			// 
			// FldMnuCopy
			// 
			this.FldMnuCopy.Name = "FldMnuCopy";
			this.FldMnuCopy.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.C)));
			this.FldMnuCopy.Size = new System.Drawing.Size(171, 22);
			this.FldMnuCopy.Text = "コピー";
			this.FldMnuCopy.Click += new System.EventHandler(this.FldMnuCopy_Click);
			// 
			// FldMnuPaste
			// 
			this.FldMnuPaste.Name = "FldMnuPaste";
			this.FldMnuPaste.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.V)));
			this.FldMnuPaste.Size = new System.Drawing.Size(171, 22);
			this.FldMnuPaste.Text = "ペースト";
			this.FldMnuPaste.Click += new System.EventHandler(this.FldMnuPaste_Click);
			// 
			// toolStripMenuItem1
			// 
			this.toolStripMenuItem1.Name = "toolStripMenuItem1";
			this.toolStripMenuItem1.Size = new System.Drawing.Size(168, 6);
			// 
			// FldMnuEdit
			// 
			this.FldMnuEdit.Name = "FldMnuEdit";
			this.FldMnuEdit.Size = new System.Drawing.Size(171, 22);
			this.FldMnuEdit.Text = "編集(&E)";
			this.FldMnuEdit.Click += new System.EventHandler(this.FldMnuEdit_Click);
			// 
			// MainTabCtrl
			// 
			this.MainTabCtrl.Controls.Add(this.MapTabPage);
			this.MainTabCtrl.Controls.Add(this.EnemyTabPage);
			this.MainTabCtrl.Dock = System.Windows.Forms.DockStyle.Fill;
			this.MainTabCtrl.Location = new System.Drawing.Point(0, 0);
			this.MainTabCtrl.Name = "MainTabCtrl";
			this.MainTabCtrl.SelectedIndex = 0;
			this.MainTabCtrl.Size = new System.Drawing.Size(392, 480);
			this.MainTabCtrl.TabIndex = 0;
			// 
			// MapTabPage
			// 
			this.MapTabPage.Controls.Add(this.MapSheet);
			this.MapTabPage.Location = new System.Drawing.Point(4, 22);
			this.MapTabPage.Name = "MapTabPage";
			this.MapTabPage.Padding = new System.Windows.Forms.Padding(3);
			this.MapTabPage.Size = new System.Drawing.Size(384, 454);
			this.MapTabPage.TabIndex = 0;
			this.MapTabPage.Text = "背景オブジェクト";
			this.MapTabPage.UseVisualStyleBackColor = true;
			// 
			// MapSheet
			// 
			this.MapSheet.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
			this.MapSheet.ContextMenuStrip = this.MapMenu;
			this.MapSheet.Dock = System.Windows.Forms.DockStyle.Fill;
			this.MapSheet.Location = new System.Drawing.Point(3, 3);
			this.MapSheet.Name = "MapSheet";
			this.MapSheet.RowTemplate.Height = 21;
			this.MapSheet.Size = new System.Drawing.Size(378, 448);
			this.MapSheet.TabIndex = 0;
			this.MapSheet.SelectionChanged += new System.EventHandler(this.MapSheet_SelectionChanged);
			// 
			// MapMenu
			// 
			this.MapMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.MapMnuSelectClear,
            this.MapMnuマップ切り替え});
			this.MapMenu.Name = "MapMenu";
			this.MapMenu.Size = new System.Drawing.Size(181, 48);
			// 
			// MapMnuSelectClear
			// 
			this.MapMnuSelectClear.Name = "MapMnuSelectClear";
			this.MapMnuSelectClear.Size = new System.Drawing.Size(180, 22);
			this.MapMnuSelectClear.Text = "選択クリア(&C)";
			this.MapMnuSelectClear.Click += new System.EventHandler(this.MapMnuSelectClear_Click);
			// 
			// MapMnuマップ切り替え
			// 
			this.MapMnuマップ切り替え.Name = "MapMnuマップ切り替え";
			this.MapMnuマップ切り替え.Size = new System.Drawing.Size(180, 22);
			this.MapMnuマップ切り替え.Text = "マップ切り替え(&M)";
			this.MapMnuマップ切り替え.Click += new System.EventHandler(this.MapMnuマップ切り替え_Click);
			// 
			// EnemyTabPage
			// 
			this.EnemyTabPage.Controls.Add(this.EnemySheet);
			this.EnemyTabPage.Location = new System.Drawing.Point(4, 22);
			this.EnemyTabPage.Name = "EnemyTabPage";
			this.EnemyTabPage.Padding = new System.Windows.Forms.Padding(3);
			this.EnemyTabPage.Size = new System.Drawing.Size(384, 454);
			this.EnemyTabPage.TabIndex = 1;
			this.EnemyTabPage.Text = "敵オブジェクト";
			this.EnemyTabPage.UseVisualStyleBackColor = true;
			// 
			// EnemySheet
			// 
			this.EnemySheet.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
			this.EnemySheet.ContextMenuStrip = this.EnemyMenu;
			this.EnemySheet.Dock = System.Windows.Forms.DockStyle.Fill;
			this.EnemySheet.Location = new System.Drawing.Point(3, 3);
			this.EnemySheet.Name = "EnemySheet";
			this.EnemySheet.RowTemplate.Height = 21;
			this.EnemySheet.Size = new System.Drawing.Size(378, 448);
			this.EnemySheet.TabIndex = 0;
			// 
			// EnemyMenu
			// 
			this.EnemyMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.EneMnuSelectClear});
			this.EnemyMenu.Name = "EnemyMenu";
			this.EnemyMenu.Size = new System.Drawing.Size(155, 26);
			// 
			// EneMnuSelectClear
			// 
			this.EneMnuSelectClear.Name = "EneMnuSelectClear";
			this.EneMnuSelectClear.Size = new System.Drawing.Size(154, 22);
			this.EneMnuSelectClear.Text = "選択クリア(&C)";
			this.EneMnuSelectClear.Click += new System.EventHandler(this.EneMnuSelectClear_Click);
			// 
			// MainTimer
			// 
			this.MainTimer.Enabled = true;
			this.MainTimer.Tick += new System.EventHandler(this.MainTimer_Tick);
			// 
			// North
			// 
			this.North.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.NApp,
            this.NVew,
            this.NEdt,
            this.NTst});
			this.North.Location = new System.Drawing.Point(0, 0);
			this.North.Name = "North";
			this.North.Size = new System.Drawing.Size(798, 26);
			this.North.TabIndex = 1;
			this.North.Text = "menuStrip1";
			// 
			// NApp
			// 
			this.NApp.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.NAQuit,
            this.NANoSaveQuit});
			this.NApp.Name = "NApp";
			this.NApp.Size = new System.Drawing.Size(60, 22);
			this.NApp.Text = "App(&A)";
			// 
			// NAQuit
			// 
			this.NAQuit.Name = "NAQuit";
			this.NAQuit.Size = new System.Drawing.Size(178, 22);
			this.NAQuit.Text = "終了(&X)";
			this.NAQuit.Click += new System.EventHandler(this.NAQuit_Click);
			// 
			// NANoSaveQuit
			// 
			this.NANoSaveQuit.Name = "NANoSaveQuit";
			this.NANoSaveQuit.Size = new System.Drawing.Size(178, 22);
			this.NANoSaveQuit.Text = "保存せずに終了(&Z)";
			this.NANoSaveQuit.Click += new System.EventHandler(this.NANoSaveQuit_Click);
			// 
			// NVew
			// 
			this.NVew.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.NVLayer,
            this.NVewNoDispGridLine});
			this.NVew.Name = "NVew";
			this.NVew.Size = new System.Drawing.Size(62, 22);
			this.NVew.Text = "表示(&V)";
			// 
			// NVLayer
			// 
			this.NVLayer.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.NV背景Layer,
            this.NV敵Layer});
			this.NVLayer.Name = "NVLayer";
			this.NVLayer.Size = new System.Drawing.Size(203, 22);
			this.NVLayer.Text = "レイヤー(&L)";
			// 
			// NV背景Layer
			// 
			this.NV背景Layer.Name = "NV背景Layer";
			this.NV背景Layer.ShortcutKeys = System.Windows.Forms.Keys.F11;
			this.NV背景Layer.Size = new System.Drawing.Size(177, 22);
			this.NV背景Layer.Text = "背景レイヤー";
			this.NV背景Layer.Click += new System.EventHandler(this.NV背景Layer_Click);
			// 
			// NV敵Layer
			// 
			this.NV敵Layer.Name = "NV敵Layer";
			this.NV敵Layer.ShortcutKeys = System.Windows.Forms.Keys.F12;
			this.NV敵Layer.Size = new System.Drawing.Size(177, 22);
			this.NV敵Layer.Text = "敵レイヤー";
			this.NV敵Layer.Click += new System.EventHandler(this.NV敵Layer_Click);
			// 
			// NVewNoDispGridLine
			// 
			this.NVewNoDispGridLine.Name = "NVewNoDispGridLine";
			this.NVewNoDispGridLine.Size = new System.Drawing.Size(203, 22);
			this.NVewNoDispGridLine.Text = "グリッド線の非表示(&G)";
			this.NVewNoDispGridLine.Click += new System.EventHandler(this.NVewNoDispGridLine_Click);
			// 
			// NEdt
			// 
			this.NEdt.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.NEdtLeftClickDeHaichi});
			this.NEdt.Name = "NEdt";
			this.NEdt.Size = new System.Drawing.Size(61, 22);
			this.NEdt.Text = "編集(&E)";
			// 
			// NEdtLeftClickDeHaichi
			// 
			this.NEdtLeftClickDeHaichi.Name = "NEdtLeftClickDeHaichi";
			this.NEdtLeftClickDeHaichi.ShortcutKeys = System.Windows.Forms.Keys.F10;
			this.NEdtLeftClickDeHaichi.Size = new System.Drawing.Size(220, 22);
			this.NEdtLeftClickDeHaichi.Text = "左クリックで配置(&H)";
			this.NEdtLeftClickDeHaichi.Click += new System.EventHandler(this.NEdtLeftClickDeHaichi_Click);
			// 
			// NTst
			// 
			this.NTst.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.NTstFromTop,
            this.NTstFromSelect});
			this.NTst.Name = "NTst";
			this.NTst.Size = new System.Drawing.Size(110, 22);
			this.NTst.Text = "テストプレイ(&T)";
			// 
			// NTstFromTop
			// 
			this.NTstFromTop.Name = "NTstFromTop";
			this.NTstFromTop.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Shift | System.Windows.Forms.Keys.F5)));
			this.NTstFromTop.Size = new System.Drawing.Size(206, 22);
			this.NTstFromTop.Text = "最初から";
			this.NTstFromTop.Click += new System.EventHandler(this.NTstFromTop_Click);
			// 
			// NTstFromSelect
			// 
			this.NTstFromSelect.Name = "NTstFromSelect";
			this.NTstFromSelect.ShortcutKeys = System.Windows.Forms.Keys.F5;
			this.NTstFromSelect.Size = new System.Drawing.Size(206, 22);
			this.NTstFromSelect.Text = "選択された位置から";
			this.NTstFromSelect.Click += new System.EventHandler(this.NTstFromSelect_Click);
			// 
			// MainWin
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(798, 506);
			this.Controls.Add(this.MainSplit);
			this.Controls.Add(this.North);
			this.MainMenuStrip = this.North;
			this.Name = "MainWin";
			this.Text = "Editor";
			this.Activated += new System.EventHandler(this.MainWin_Activated);
			this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.MainWin_FormClosed);
			this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainWin_FormClosing);
			this.MainSplit.Panel1.ResumeLayout(false);
			this.MainSplit.Panel2.ResumeLayout(false);
			this.MainSplit.ResumeLayout(false);
			this.LeftSplit.Panel1.ResumeLayout(false);
			this.LeftSplit.Panel2.ResumeLayout(false);
			this.LeftSplit.ResumeLayout(false);
			this.LTPanel.ResumeLayout(false);
			this.LTPanel.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.FieldSheet)).EndInit();
			this.FieldMenu.ResumeLayout(false);
			this.MainTabCtrl.ResumeLayout(false);
			this.MapTabPage.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.MapSheet)).EndInit();
			this.MapMenu.ResumeLayout(false);
			this.EnemyTabPage.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.EnemySheet)).EndInit();
			this.EnemyMenu.ResumeLayout(false);
			this.North.ResumeLayout(false);
			this.North.PerformLayout();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.SplitContainer MainSplit;
		private System.Windows.Forms.SplitContainer LeftSplit;
		private System.Windows.Forms.TabControl MainTabCtrl;
		private System.Windows.Forms.TabPage MapTabPage;
		private System.Windows.Forms.DataGridView MapSheet;
		private System.Windows.Forms.TabPage EnemyTabPage;
		private System.Windows.Forms.DataGridView EnemySheet;
		private System.Windows.Forms.HScrollBar FieldScroll;
		private System.Windows.Forms.Timer MainTimer;
		private System.Windows.Forms.MenuStrip North;
		private System.Windows.Forms.ToolStripMenuItem NApp;
		private System.Windows.Forms.ToolStripMenuItem NVew;
		private System.Windows.Forms.ToolStripMenuItem NVLayer;
		private System.Windows.Forms.ToolStripMenuItem NV背景Layer;
		private System.Windows.Forms.ToolStripMenuItem NV敵Layer;
		private System.Windows.Forms.ContextMenuStrip FieldMenu;
		private System.Windows.Forms.ToolStripMenuItem FldMnuSelectClear;
		private System.Windows.Forms.ToolStripMenuItem FldMnu配置;
		private System.Windows.Forms.ToolStripMenuItem NAQuit;
		private System.Windows.Forms.ToolStripMenuItem FldMnuErase;
		private System.Windows.Forms.ContextMenuStrip MapMenu;
		private System.Windows.Forms.ToolStripMenuItem MapMnuSelectClear;
		private System.Windows.Forms.ToolStripMenuItem MapMnuマップ切り替え;
		private System.Windows.Forms.ContextMenuStrip EnemyMenu;
		private System.Windows.Forms.ToolStripMenuItem EneMnuSelectClear;
		private System.Windows.Forms.ToolStripMenuItem FldMnuCopy;
		private System.Windows.Forms.ToolStripMenuItem NANoSaveQuit;
		private System.Windows.Forms.ToolStripMenuItem FldMnuPaste;
		private System.Windows.Forms.DataGridView FieldSheet;
		private System.Windows.Forms.ToolStripSeparator toolStripMenuItem2;
		private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
		private System.Windows.Forms.ToolStripMenuItem FldMnuEdit;
		private System.Windows.Forms.ToolStripMenuItem NEdt;
		private System.Windows.Forms.ToolStripMenuItem NEdtLeftClickDeHaichi;
		private System.Windows.Forms.ToolStripMenuItem NVewNoDispGridLine;
		private System.Windows.Forms.ToolStripMenuItem NTst;
		private System.Windows.Forms.ToolStripMenuItem NTstFromTop;
		private System.Windows.Forms.ToolStripMenuItem NTstFromSelect;
		private System.Windows.Forms.Panel LTPanel;
		private System.Windows.Forms.Label SttF12;
		private System.Windows.Forms.Label SttF11;
		private System.Windows.Forms.Label SttF10;
	}
}

