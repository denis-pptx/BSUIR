using System.Diagnostics;
using System.ComponentModel;
using System.Runtime.Versioning;
using sMkTaskManager.Classes;
using sMkTaskManager.Controls;
using System.Drawing.Drawing2D;
namespace sMkTaskManager.Forms;

[DesignerCategory("Component"), SupportedOSPlatform("windows")]
internal class tabGpu : UserControl, ITaskManagerTab {
    private readonly Stopwatch _stopWatch = new();
    private readonly TaskManagerGPUCollection GPUs = new();
    private HashSet<string> ColsGpus = new();
    private sMkPerfChart[] Charts;

    private sMkListView lv;
    private ImageList il;
    private Label lblGpuChart;
    private sMkPerfChart chartGpu;

    private TableLayoutPanel tlp;

    public event EventHandler? RefreshStarts;
    public event EventHandler? RefreshComplete;
    public event EventHandler? ForceRefreshClicked;

    private IContainer? components = null;
    protected override void Dispose(bool disposing) {
        if (disposing && (components != null)) { components.Dispose(); }
        base.Dispose(disposing);
    }

    public tabGpu() {
        InitializeComponent();
        InitializeExtras();
        Extensions.CascadingDoubleBuffer(this);
    }
    private void InitializeComponent() {
        components = new Container();
        il = new ImageList(components);
        tlp = new TableLayoutPanel();
        chartGpu = new sMkPerfChart();
        lblGpuChart = new Label();
        lv = new sMkListView();
        tlp.SuspendLayout();
        SuspendLayout();
        // 
        // il
        // 
        il.ColorDepth = ColorDepth.Depth32Bit;
        il.ImageSize = new Size(16, 16);
        il.TransparentColor = Color.Transparent;
        // 
        // tlp
        // 
        tlp.ColumnCount = 1;
        tlp.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 50F));
        tlp.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 50F));
        tlp.Controls.Add(lblGpuChart, 0, 0);
        tlp.Controls.Add(chartGpu, 0, 1);
        tlp.Controls.Add(lv, 0, 2);
        tlp.Dock = DockStyle.Fill;
        tlp.Location = new Point(0, 0);
        tlp.Name = "tlp";
        tlp.RowCount = 3;
        tlp.RowStyles.Add(new RowStyle(SizeType.Percent, 5F));
        tlp.RowStyles.Add(new RowStyle(SizeType.Percent, 85F));
        tlp.RowStyles.Add(new RowStyle(SizeType.Percent, 10F));
        tlp.Size = new Size(600, 600);
        tlp.TabIndex = 0;

    
        // 
        // chartGpu
        // 
        chartGpu.AntiAliasing = false;
        chartGpu.BackColor = Color.Black;
        chartGpu.BackColorShade = Color.FromArgb(0, 0, 0);
        chartGpu.BackSolid = false;
        chartGpu.BorderStyle = Border3DStyle.Sunken;
        tlp.SetColumnSpan(chartGpu, 2);
        chartGpu.DetailsOnHover = false;
        chartGpu.DisplayAverage = false;
        chartGpu.DisplayIndexes = false;
        chartGpu.DisplayLegends = false;
        chartGpu.Dock = DockStyle.Fill;
        chartGpu.GridSpacing = 10;
        chartGpu.LegendSpacing = 35;
        chartGpu.LightColors = false;
        chartGpu.Location = new Point(2, 22);
        chartGpu.Margin = new Padding(2);
        chartGpu.MaxValue = 0D;
        chartGpu.Name = "chartGpu";
        chartGpu.ScaleMode = sMkPerfChart.ScaleModes.Absolute;
        chartGpu.ShadeBackground = false;
        chartGpu.Size = new Size(596, 109);
        chartGpu.TabIndex = 5;
        chartGpu.TabStop = false;
        chartGpu.ValueSpacing = 2;
        chartGpu.ValuesSuffix = "";
        // 
        // lblGpuChart
        // 
        lblGpuChart.Dock = DockStyle.Fill;
        lblGpuChart.Location = new Point(3, 1);
        lblGpuChart.Margin = new Padding(3, 1, 3, 0);
        lblGpuChart.Name = "lblGpuChart";
        lblGpuChart.Size = new Size(594, 19);
        lblGpuChart.TabIndex = 3;
        lblGpuChart.Text = "GPU Total Usage";
        lblGpuChart.TextAlign = ContentAlignment.BottomLeft;
        // 
        // lv
        // 
        lv.AlternateRowColors = false;
        lv.BorderStyle = BorderStyle.FixedSingle;
        lv.Dock = DockStyle.Fill;
        lv.FullRowSelect = true;
        lv.Location = new Point(3, 523);
        lv.MultiSelect = false;
        lv.Name = "lv";
        lv.Size = new Size(594, 74);
        lv.Sortable = true;
        lv.SortColumn = -1;
        lv.Sorting = SortOrder.Ascending;
        lv.TabIndex = 18;
        lv.UseCompatibleStateImageBehavior = false;
        lv.View = View.Details;
        // 
        // tabGpu
        // 
        Controls.Add(tlp);
        Name = "tabGpu";
        Size = new Size(600, 600);
        tlp.ResumeLayout(false);
        ResumeLayout(false);
    }
    private void InitializeExtras() {
        Charts = new[] { chartGpu };
        foreach (sMkPerfChart g in Charts) {
            g.SetIndexes("Gpu0");
            g.BackColorShade = Color.FromArgb(0, 0, 0);
            g.ScaleMode = sMkPerfChart.ScaleModes.Absolute;
        }

        lv.ContentType = typeof(TaskManagerGPU);
        lv.DataSource = GPUs.DataExporter;
        lv.StateImageList = il;
        il.Images.Clear();
        lv.HideSelection = true;

        lv.ColumnReordered += OnListViewColumnReordered;
        lv.SizeChanged += OnListViewSizeChanged;
        lv.ColumnWidthChanging += OnListViewColumnWidthChanging;
        lv.ColumnWidthChanged += OnListViewColumnWidthChanged;
    }

    private void OnListViewColumnReordered(object? sender, ColumnReorderedEventArgs e) {
        if (e.Header!.Text == "ID") { e.Cancel = true; }
        if (e.Header!.Text == "Name") { e.Cancel = true; }
        if (e.NewDisplayIndex == 0) { e.Cancel = true; }
    }
    private void OnListViewSizeChanged(object? sender, EventArgs e) {
        if (lv.Columns.Count >= 1 && lv.Width > 200) {
            lv.Columns[0].Width = Math.Max(50, lv.Width - lv.TotalColumnsWidth(0));
        }
    }
    private void OnListViewColumnWidthChanging(object? sender, ColumnWidthChangingEventArgs e) {
        if (lv.Visible && lv.Columns.Count >= 1 && e.ColumnIndex != 0) {
            lv.Columns[0].Width = Math.Max(50, lv.Width - lv.TotalColumnsWidth(0));
        }
    }
    private void OnListViewColumnWidthChanged(object? sender, ColumnWidthChangedEventArgs e) {
        // Dont force this, its crashing unexpectedly
        // if (e.ColumnIndex == 0) { lv.Columns[0].Width = Math.Max(50, lv.Width - lv.TotalColumnsWidth(0)); }
    }
    private Color PopulateAndGetAdapterColor(short number) {
        var thisColor = number switch {
            1 => Color.CornflowerBlue,
            2 => Color.Khaki,
            3 => Color.LightSteelBlue,
            4 => Color.MediumTurquoise,
            5 => Color.PaleGreen,
            _ => Color.DarkGray,
        };
        if (!il.Images.ContainsKey(number.ToString())) {
            Bitmap bmp = new(16, 16);
            Graphics g = Graphics.FromImage(bmp);
            using (SolidBrush thisBrush = new(thisColor)) {
                g.FillRectangle(thisBrush, 1, 1, 14, 14);
            }
            using (Pen thisPen = new(Color.Black, 1)) {
                g.DrawRectangle(thisPen, 1, 1, 14, 14);
            }
            il.Images.Add(number.ToString(), bmp);
        }
        return thisColor;
    }

    private void PopulateGraphIndexes() {
        foreach (sMkPerfChart g in Charts) {
            if (GPUs.Count == 1) { g.SetIndexes("GPU1"); }
            if (GPUs.Count == 2) { g.SetIndexes("GPU1", "GPU2"); }
            if (GPUs.Count == 3) { g.SetIndexes("GPU1", "GPU2", "GPU3"); }
            if (GPUs.Count == 4) { g.SetIndexes("GPU1", "GPU2", "GPU3", "GPU4"); }
            if (GPUs.Count >= 5) { g.SetIndexes("GPU1", "GPU2", "GPU3", "GPU4", "GPU5"); }

            if (GPUs.Count >= 1) g.PenGraph1.Color = GPUs[0].Color;
            if (GPUs.Count >= 2) g.PenGraph2.Color = GPUs[1].Color;
            if (GPUs.Count >= 3) g.PenGraph3.Color = GPUs[2].Color;
            if (GPUs.Count >= 4) g.PenGraph4.Color = GPUs[3].Color;
            if (GPUs.Count >= 5) g.PenGraph5.Color = GPUs[4].Color;
        }
    }
    private void PopulateGraphValues() {
        if (GPUs.Count == 1) {
            chartGpu.AddValue(GPUs[0].UsageValue);

        } else if (GPUs.Count == 2) {
            chartGpu.AddValue(GPUs[0].UsageValue, GPUs[1].UsageValue);
        
        } else if (GPUs.Count == 3) {
            chartGpu.AddValue(GPUs[0].UsageValue, GPUs[1].UsageValue, GPUs[2].UsageValue);
          
          
        } else if (GPUs.Count == 4) {
            chartGpu.AddValue(GPUs[0].UsageValue, GPUs[1].UsageValue, GPUs[2].UsageValue, GPUs[3].UsageValue);

          
        } else if (GPUs.Count >= 5) {
            chartGpu.AddValue(GPUs[0].UsageValue, GPUs[1].UsageValue, GPUs[2].UsageValue, GPUs[3].UsageValue, GPUs[4].UsageValue);
           
        }
    }

    public void Feature_ForceRefresh() {
        lv.SuspendLayout();
        GPUs.Clear();
        lv.Items.Clear();
        Refresher(true);
        lv.ResumeLayout();
        ForceRefreshClicked?.Invoke(this, EventArgs.Empty);
    }

    public sMkListView? ListView => lv;
    public string Title { get; set; } = "GPUs";
    public string Description { get; set; } = "GPU Performance";
    public string TimmingKey => "GPU";
    public long TimmingValue => _stopWatch.ElapsedMilliseconds;
    public bool CanSelectColumns => true;
    public void ForceRefresh() => Feature_ForceRefresh();
    public TaskManagerColumnTypes ColumnType => TaskManagerColumnTypes.GPUs;
    public ListView.ColumnHeaderCollection? GetColumns() => lv.Columns;
    public void SetColumns(in ListView.ListViewItemCollection colItems) {
        lv.SetColumns(colItems);
        ColsGpus = lv.Columns.Cast<ColumnHeader>().Select(x => x.Name).ToHashSet()!;
    }

    private void RefresherDoWork(bool firstTime = false) {
        RefreshStarts?.Invoke(this, EventArgs.Empty);
        if (GPUs.Count == 0) firstTime = true;

        if (firstTime) {
            short i = 0;
            foreach (TaskManagerGPU a in TaskManagerGPU.GetAdaptersList()) {
                i++;
                if (i > 5) break;
                try {
                    a.Load();
                    a.Color = PopulateAndGetAdapterColor(i);
                    a.StateImageIndex = il.Images.IndexOfKey(i.ToString());
                    GPUs.Add(a);
                } catch (Exception ex) { Shared.DebugTrap(ex, 311); }
            }
            PopulateGraphIndexes();
            lv.Scrollable = false;
            Title = lv.Items.Count > 1 ? "GPUs" : "GPU";
            tlp.RowStyles[tlp.GetRow(lv)].Height = 30 + (lv.Items.Count * 20) + 10;
            if (lv.Columns.Count > 0) lv.Columns[0].Width = Math.Max(50, lv.Width - lv.TotalColumnsWidth(0));
        } else {
            foreach (TaskManagerGPU g in GPUs) {
                try {
                    g!.Refresh();
                } catch (Exception ex) { Shared.DebugTrap(ex, 312); }
            }
            PopulateGraphValues();
        }

        RefreshComplete?.Invoke(this, EventArgs.Empty);
    }
    public void Refresher(bool firstTime = false) {
        _stopWatch.Restart();
        if (InvokeRequired) {
            Invoke(() => RefresherDoWork(firstTime));
        } else {
            RefresherDoWork();
        }
        _stopWatch.Stop();
    }
    public void LoadSettings() {
        Settings.LoadColsInformation(ColumnType, lv, ref ColsGpus);
        chartGpu.BackSolid = Settings.Performance.Solid;
        chartGpu.AntiAliasing = Settings.Performance.AntiAlias;
        chartGpu.ShadeBackground = false; // Settings.Performance.ShadeBackground;
        chartGpu.DisplayAverage = false;  // Settings.Performance.DisplayAverages;
        chartGpu.DisplayLegends = false;  // Settings.Performance.DisplayLegends;
        chartGpu.DisplayIndexes = true;   // Settings.Performance.DisplayIndexes;
        chartGpu.DetailsOnHover = false;  // Settings.Performance.DisplayOnHover;
        chartGpu.ValueSpacing = Settings.Performance.ValueSpacing;
        chartGpu.GridSpacing = Settings.Performance.GridSize;
        chartGpu.PenGridVertical.DashStyle = (DashStyle)Settings.Performance.VerticalGridStyle;
        chartGpu.PenGridVertical.Color = Settings.Performance.VerticalGridColor;
        chartGpu.PenGridHorizontal.DashStyle = (DashStyle)Settings.Performance.HorizontalGridStyle;
        chartGpu.PenGridHorizontal.Color = Settings.Performance.HorizontalGridColor;
        chartGpu.PenAverage.DashStyle = (DashStyle)Settings.Performance.AverageLineStyle;
        chartGpu.PenAverage.Color = Settings.Performance.AverageLineColor;
        chartGpu.LightColors = Settings.Performance.LightColors;
   

    }

}
