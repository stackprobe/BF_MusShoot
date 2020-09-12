using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Editor
{
	public class FieldCellData
	{
		public int Index;
		public ResourceDataList CommonParamValueList;
		public ResourceDataList ParamValueList;

		public FieldCellData(int index, ResourceDataList cpvl, ResourceDataList pvl)
		{
			this.Index = index;
			this.CommonParamValueList = cpvl;
			this.ParamValueList = pvl;
		}

		public void SetTilePos(int mapIndex, int xPos, int yPos)
		{
			this.ParamValueList.SetValue(0, "" + mapIndex);
			this.ParamValueList.SetValue(1, "" + xPos);
			this.ParamValueList.SetValue(2, "" + yPos);
		}
		public int[] GetTilePos()
		{
			return new int[]
			{
				Tools.ParseInt(this.ParamValueList.GetValue(0)), // mapIndex
				Tools.ParseInt(this.ParamValueList.GetValue(1)), // xPos
				Tools.ParseInt(this.ParamValueList.GetValue(2)), // yPos
			};
		}

		public static void AddToText(List<string> text, FieldCellData fcd)
		{
			if (fcd != null)
			{
				text.Add("" + fcd.Index);
				Tools.AddToValues<string>(text, fcd.CommonParamValueList.GetValueList_RTrim());
				text.Add("");
				Tools.AddToValues<string>(text, fcd.ParamValueList.GetValueList_RTrim());
			}
			text.Add("");
		}
		public FieldCellData GetClone()
		{
			return new FieldCellData(
				this.Index,
				this.CommonParamValueList.GetClone(),
				this.ParamValueList.GetClone()
				);
		}
	}
}
