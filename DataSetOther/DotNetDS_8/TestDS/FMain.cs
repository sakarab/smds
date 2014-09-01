using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace TestDS
{
    public partial class frmMain : Form
    {
        public frmMain()
        {
            InitializeComponent();
        }

        private int do_loop(tblFiles.tblFilesDataTable tbl)
        {
            int result = 0;

            for (int n = 0, eend = tbl.Rows.Count; n < eend; ++n)
                if (tbl[n].IsPathIDNull())
                    ++result;
            return (result);
        }

        private void dsDatasetModify_1(tblFiles.tblFilesDataTable ds, String descr)
        {
            for (int n = 0, eend = ds.Rows.Count; n < eend; ++n)
            {
                tblFiles.tblFilesRow row = ds[n];

                row.BeginEdit();
                try
                {
                    row.FileID = n;
                    row.fSize = n;
                    row.Description = descr;
                }
                finally
                {
                    row.EndEdit();
                }
            }
        }

        private void dsDatasetModify_2(tblFiles.tblFilesDataTable ds, String descr)
        {
            for (int n = 0, eend = ds.Rows.Count; n < eend; ++n)
            {
                tblFiles.tblFilesRow row = ds[n];

                row.BeginEdit();
                try
                {
                    row.FileID = n;
                    row.fSize = n;
                    row.Description = descr;
                }
                finally
                {
                    row.EndEdit();
                }
            }
        }

        private DataRow[] CreateIndex_1g(tblFiles.tblFilesDataTable ds)
        {
            return (ds.Select("", "PathID DESC"));
        }

        private DataRow[] CreateIndex_2g(tblFiles.tblFilesDataTable ds)
        {
            return (ds.Select("", "PathID,fSize"));
        }

        private void AddRecords(tblFiles.tblFilesDataTable ds)
        {
            for (int n = 0; n < 20000; ++n)
            {
                tblFiles.tblFilesRow aa = ds.NewtblFilesRow();

                aa.FileID = n;
                aa.PathID = n;
                aa.fSize = n;

                ds.AddtblFilesRow(aa);
            }
        }

        private int Find_2g(DataView view)
        {
            return (view.Find(new Object[] { 18999, 18999 }));
        }

        int foo(int loc, DataView view)
        {
            if (loc >= 0)
                return ((int)view[loc]["PathID"] + (int)view[loc]["fSize"]);
            else
                return (0);
        }

        private void btnDatasetModify_Click(object sender, EventArgs e)
        {
            tblFilesTableAdapters.tblFilesTableAdapter  ta = new tblFilesTableAdapters.tblFilesTableAdapter();
            tblFiles.tblFilesDataTable                  ds = tblFiles._tblFiles;

            ta.Fill( ds );
            dsDatasetModify_1(ds, "File");
            dsDatasetModify_2(ds, "File");
            do_loop(ds);

            DataRow[]   aa = CreateIndex_1g(ds);

            aa = CreateIndex_2g(ds);

            AddRecords(ds);

            DataView view = new DataView(ds, "", "PathID,fSize", DataViewRowState.CurrentRows);

            for ( int n = 0 ; n < 100 ; ++n )
                foo( Find_2g(view), view );

            MessageBox.Show("Done");
        }
    }
}