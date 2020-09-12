using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Editor
{
	public class FieldTable
	{
		public List<FieldCell[]> Table = new List<FieldCell[]>(); // [x][y]

		public FieldTable(ResourceData backReader, ResourceData frontReader)
		{
			while (backReader.HasValue() || frontReader.HasValue())
			{
				FieldCell[] column = new FieldCell[Consts.FIELDMAP_H];

				for (int y = 0; y < Consts.FIELDMAP_H; y++)
				{
					column[y] = new FieldCell(
						this.GetFieldCellData(backReader),
						this.GetFieldCellData(frontReader)
						);
				}
				this.Table.Add(column);
			}
		}
		public FieldCellData GetFieldCellData(ResourceData reader)
		{
			string index_val = reader.ReadValue();

			if (index_val == ResourceData.DEFAULT_VALUE)
				return null;

			int index = Tools.ParseInt(index_val);
			ResourceDataList pvl1 = reader.ReadBlock();
			ResourceDataList pvl2 = reader.ReadBlock();

			return new FieldCellData(index, pvl1, pvl2);
		}

		public int Width
		{
			get
			{
				return this.Table.Count;
			}
		}
		public int Height
		{
			get
			{
				return Consts.FIELDMAP_H;
			}
		}

		public void AddColumn()
		{
			FieldCell[] column = new FieldCell[Consts.FIELDMAP_H];

			for (int y = 0; y < Consts.FIELDMAP_H; y++)
			{
				column[y] = new FieldCell(null, null);
			}
			this.Table.Add(column);
		}
		public FieldCell GetCell(int x, int y)
		{
			while (this.Width <= x)
			{
				this.AddColumn();
			}
			return this.Table[x][y];
		}
	}
}
