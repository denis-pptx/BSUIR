using System.ComponentModel;
using System.Diagnostics;
using System.Runtime.Versioning;
using sMkTaskManager.Classes;
using sMkTaskManager.Controls;
namespace sMkTaskManager.Forms;

[DesignerCategory("Component"), SupportedOSPlatform("windows")]
internal partial class tabPerformance : UserControl, ITaskManagerTab {
    private readonly Stopwatch _stopWatch = new();
    internal TaskManagerSystem System = new();

    public event EventHandler? ForceRefreshClicked;
    public event EventHandler? RefreshStarts;
    public event EventHandler? RefreshComplete;

    #region "Form Controls"
    private TableLayoutPanel tlpMain;
    private Label lblCpuMeter;
    private Label lblMemMeter;
    private Label lblIOMeter;
    private Label lblDiskMeter;
    private Label lblNetMeter;
    private sMkPerfMeter meterCpu;
    private sMkPerfMeter meterMem;
    private sMkPerfMeter meterIO;
    private sMkPerfMeter meterDisk;
    private sMkPerfMeter meterNet;
    #endregion
  

    public tabPerformance() {
        InitializeComponent();
        Extensions.CascadingDoubleBuffer(this);
    }
    private void InitializeComponent() {
        tlpMain = new TableLayoutPanel();
        lblCpuMeter = new Label();
        meterCpu = new sMkPerfMeter();
        lblMemMeter = new Label();
        meterMem = new sMkPerfMeter();
        lblIOMeter = new Label();
        meterIO = new sMkPerfMeter();
        lblDiskMeter = new Label();
        meterDisk = new sMkPerfMeter();
        lblNetMeter = new Label();
        meterNet = new sMkPerfMeter();

        tlpMain.SuspendLayout();

        SuspendLayout();

        // 
        // tlpMain
        // 
        tlpMain.ColumnCount = 5;
        for (int i = 0; i < tlpMain.ColumnCount; i++)
        {
            tlpMain.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 20F));
        }

        // lblCpuMeter и meterCpu в первой колонке
        tlpMain.Controls.Add(lblCpuMeter, 0, 0);
        tlpMain.Controls.Add(meterCpu, 0, 1);

        // lblMemMeter и meterMem во второй колонке
        tlpMain.Controls.Add(lblMemMeter, 1, 0);
        tlpMain.Controls.Add(meterMem, 1, 1);

        // lblIOMeter и meterIO в третьей колонке
        tlpMain.Controls.Add(lblIOMeter, 2, 0);
        tlpMain.Controls.Add(meterIO, 2, 1);

        // lblDiskMeter и meterDisk в четвёртой колонке
        tlpMain.Controls.Add(lblDiskMeter, 3, 0);
        tlpMain.Controls.Add(meterDisk, 3, 1);

        // lblNetMeter и meterNet в пятой колонке
        tlpMain.Controls.Add(lblNetMeter, 4, 0);
        tlpMain.Controls.Add(meterNet, 4, 1);

        tlpMain.Dock = DockStyle.Fill;
        tlpMain.Location = new Point(0, 0);
        tlpMain.Name = "tlpMain";
        tlpMain.Padding = new Padding(0, 3, 0, 0);
        tlpMain.RowCount = 2; 
        tlpMain.RowStyles.Add(new RowStyle(SizeType.Absolute, 16F)); // Задаём высоту для первой строки
        tlpMain.RowStyles.Add(new RowStyle(SizeType.Percent, 100F)); // Вторая строка занимает всё оставшееся место
        tlpMain.Size = new Size(600, 600);
        tlpMain.TabIndex = 0;

        // 
        // lblCpuMeter
        // 
        lblCpuMeter.Dock = DockStyle.Fill;
        lblCpuMeter.Location = new Point(7, 3);
        lblCpuMeter.Margin = new Padding(7, 0, 3, 0);
        lblCpuMeter.Name = "lblCpuMeter";
        lblCpuMeter.Size = new Size(70, 16);
        lblCpuMeter.TabIndex = 1;
        lblCpuMeter.Text = "CPU Usage";
        lblCpuMeter.TextAlign = ContentAlignment.BottomCenter;

        // 
        // meterCpu
        // 
        meterCpu.BackColor = Color.Black;
        meterCpu.BarBackColor = Color.DarkGreen;
        meterCpu.BarForeColor = Color.Lime;
        meterCpu.BorderStyle = Border3DStyle.Sunken;
        meterCpu.Dock = DockStyle.Fill;
        meterCpu.HistoryValues = 10;
        meterCpu.LightColors = false;
        meterCpu.Location = new Point(7, 21);
        meterCpu.Margin = new Padding(7, 2, 3, 2);
        meterCpu.Name = "meterCpu";
        meterCpu.ScaleMode = sMkPerfMeter.ScaleModes.Absolute;
        meterCpu.Size = new Size(70, 69);
        meterCpu.TabIndex = 3;
        meterCpu.TabStop = false;

        // 
        // lblMemMeter
        // 
        lblMemMeter.Dock = DockStyle.Fill;
        lblMemMeter.Location = new Point(7, 92);
        lblMemMeter.Margin = new Padding(7, 0, 3, 0);
        lblMemMeter.Name = "lblMemMeter";
        lblMemMeter.Size = new Size(70, 16);
        lblMemMeter.TabIndex = 5;
        lblMemMeter.Text = "Mem Usage";
        lblMemMeter.TextAlign = ContentAlignment.BottomCenter;

        // 
        // meterMem
        // 
        meterMem.BackColor = Color.Black;
        meterMem.BarBackColor = Color.FromArgb(64, 64, 0);
        meterMem.BarForeColor = Color.Yellow;
        meterMem.BorderStyle = Border3DStyle.Sunken;
        meterMem.Dock = DockStyle.Fill;
        meterMem.HistoryValues = 10;
        meterMem.LightColors = false;
        meterMem.Location = new Point(7, 110);
        meterMem.Margin = new Padding(7, 2, 3, 2);
        meterMem.Name = "meterMem";
        meterMem.ScaleMode = sMkPerfMeter.ScaleModes.Absolute;
        meterMem.Size = new Size(70, 69);
        meterMem.TabIndex = 7;
        meterMem.TabStop = false;

        // 
        // lblIOMeter
        // 
        lblIOMeter.Dock = DockStyle.Fill;
        lblIOMeter.Location = new Point(7, 182);
        lblIOMeter.Margin = new Padding(7, 1, 3, 0);
        lblIOMeter.Name = "lblIOMeter";
        lblIOMeter.Size = new Size(70, 15);
        lblIOMeter.TabIndex = 9;
        lblIOMeter.Text = "I/O Usage";
        lblIOMeter.TextAlign = ContentAlignment.BottomCenter;

        // 
        // meterIO
        // 
        meterIO.BackColor = Color.Black;
        meterIO.BarBackColor = Color.MidnightBlue;
        meterIO.BarForeColor = Color.DodgerBlue;
        meterIO.BorderStyle = Border3DStyle.Sunken;
        meterIO.Dock = DockStyle.Fill;
        meterIO.HistoryValues = 10;
        meterIO.LightColors = false;
        meterIO.Location = new Point(7, 199);
        meterIO.Margin = new Padding(7, 2, 3, 2);
        meterIO.Name = "meterIO";
        meterIO.ScaleMode = sMkPerfMeter.ScaleModes.Relative;
        meterIO.Size = new Size(70, 69);
        meterIO.TabIndex = 11;
        meterIO.TabStop = false;

        // 
        // lblDiskMeter
        // 
        lblDiskMeter.Dock = DockStyle.Fill;
        lblDiskMeter.Location = new Point(7, 271);
        lblDiskMeter.Margin = new Padding(7, 1, 3, 0);
        lblDiskMeter.Name = "lblDiskMeter";
        lblDiskMeter.Size = new Size(70, 15);
        lblDiskMeter.TabIndex = 13;
        lblDiskMeter.Text = "Disk Usage";
        lblDiskMeter.TextAlign = ContentAlignment.BottomCenter;

        // 
        // meterDisk
        // 
        meterDisk.BackColor = Color.Black;
        meterDisk.BarBackColor = Color.Sienna;
        meterDisk.BarForeColor = Color.SandyBrown;
        meterDisk.BorderStyle = Border3DStyle.Sunken;
        meterDisk.Dock = DockStyle.Fill;
        meterDisk.HistoryValues = 10;
        meterDisk.LightColors = false;
        meterDisk.Location = new Point(7, 288);
        meterDisk.Margin = new Padding(7, 2, 3, 2);
        meterDisk.Name = "meterDisk";
        meterDisk.ScaleMode = sMkPerfMeter.ScaleModes.Relative;
        meterDisk.Size = new Size(70, 69);
        meterDisk.TabIndex = 15;
        meterDisk.TabStop = false;

        // 
        // lblNetMeter
        // 
        lblNetMeter.Dock = DockStyle.Fill;
        lblNetMeter.Location = new Point(7, 360);
        lblNetMeter.Margin = new Padding(7, 1, 3, 0);
        lblNetMeter.Name = "lblNetMeter";
        lblNetMeter.Size = new Size(70, 15);
        lblNetMeter.TabIndex = 17;
        lblNetMeter.Text = "Net Usage";
        lblNetMeter.TextAlign = ContentAlignment.BottomCenter;
        // 
        // meterNet
        // 
        meterNet.BackColor = Color.Black;
        meterNet.BarBackColor = Color.Indigo;
        meterNet.BarForeColor = Color.Violet;
        meterNet.BorderStyle = Border3DStyle.Sunken;
        meterNet.Dock = DockStyle.Fill;
        meterNet.HistoryValues = 10;
        meterNet.LightColors = false;
        meterNet.Location = new Point(7, 377);
        meterNet.Margin = new Padding(7, 2, 3, 2);
        meterNet.Name = "meterNet";
        meterNet.ScaleMode = sMkPerfMeter.ScaleModes.Relative;
        meterNet.Size = new Size(70, 69);
        meterNet.TabIndex = 19;
        meterNet.TabStop = false;


        // 
        // tabPerformance
        // 
        Controls.Add(tlpMain);
        Name = "tabPerformance";
        Size = new Size(600, 600);
        Load += OnLoad;
        VisibleChanged += OnVisibleChanged;
        tlpMain.ResumeLayout(false);

        ResumeLayout(false);
    }

    private void OnLoad(object? sender, EventArgs e) {
        System.RefreshCompleted += System_RefreshCompleted;
    }
    private void OnVisibleChanged(object? sender, EventArgs e) {
        if (Visible && Shared.InitComplete && _stopWatch.ElapsedTicks == 0) {
            SuspendLayout(); Refresher(true); ResumeLayout();
        }
    }

  
    private void System_RefreshCompleted(object? sender, EventArgs e) {
        // Always set these values. regardless we are visible or not.
        meterCpu.SetValue(System.CpuUsage.Value);
        meterMem.SetValue(System.MemoryUsage, System.MemoryUsageString);
        meterIO.SetValue(System.ioDataUsage, System.ioDataUsageString);
        meterDisk.SetValue(System.DiskUsage, System.DiskUsageString);
        meterNet.SetValue(System.NetworkUsage, System.NetworkUsageString);
        // Always flush the ETW, if its active.
        Shared.ETW.Flush();
    }

    private enum PerformanceMeters {
        CPU = 1,
        Mem = 2,
        IO = 3,
        Disk = 4,
        Net = 5
    }

    public string Title { get; set; } = "Performance";
    public string Description { get; set; } = "System Performance";
    public string TimmingKey => "Perfs";
    public long TimmingValue => _stopWatch.ElapsedMilliseconds;
    public void ForceRefresh() => ForceRefreshClicked?.Invoke(this, EventArgs.Empty);

    private void RefresherDoWork() {
        RefreshStarts?.Invoke(this, EventArgs.Empty);
        System.Refresh();
        RefreshComplete?.Invoke(this, EventArgs.Empty);
    }
    public void Refresher(bool firstTime = false) {
        _stopWatch.Restart();
        if (InvokeRequired) {
            Invoke(() => RefresherDoWork());
        } else {
            RefresherDoWork();
        }
        _stopWatch.Stop();
    }
    public void LoadSettings() {
        Settings.LoadPerformance();
    }
}

