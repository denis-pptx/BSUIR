using System.ComponentModel;
using System.Diagnostics;
using System.Runtime.Versioning;
using sMkTaskManager.Classes;
using sMkTaskManager.Controls;
namespace sMkTaskManager.Forms;

[DesignerCategory("Component"), SupportedOSPlatform("windows")]
internal class tabDevices : UserControl, ITaskManagerTab {
    private ImageList il;
    private TreeView tv;
    private Label lblText;
    private Button btnRefresh;
    private CheckBox chkHidden;

    public event EventHandler? RefreshStarts;
    public event EventHandler? RefreshComplete;
    public event EventHandler? ForceRefreshClicked;

    public tabDevices() {
        InitializeComponent();
        InitializeHandlers();
    }
    private void InitializeComponent() {
        tv = new TreeView();
        il = new ImageList();
        btnRefresh = new Button();
        chkHidden = new CheckBox();
        lblText = new Label();
        SuspendLayout();
        // 
        // tv
        // 
        tv.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
        tv.BorderStyle = BorderStyle.FixedSingle;
        tv.ImageIndex = 0;
        tv.ImageList = il;
        tv.Location = new Point(6, 6);
        tv.Margin = new Padding(6, 6, 6, 0);
        tv.Name = "tv";
        tv.SelectedImageIndex = 0;
        tv.ShowLines = false;
        tv.Size = new Size(588, 559);
        tv.TabIndex = 0;
    
        // 
        // il
        // 
        il.ColorDepth = ColorDepth.Depth32Bit;
        il.ImageSize = new Size(16, 16);
        il.TransparentColor = Color.Transparent;
        // 
        // btnForceRefresh
        // 
        btnRefresh.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;
        btnRefresh.Location = new Point(505, 571);
        btnRefresh.Margin = new Padding(0, 3, 3, 3);
        btnRefresh.Name = "btnForceRefresh";
        btnRefresh.Size = new Size(89, 23);
        btnRefresh.TabIndex = 3;
        btnRefresh.Text = "Refresh";
        btnRefresh.UseVisualStyleBackColor = true;

        // 
        // chkHidden
        // 
        chkHidden.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
        chkHidden.Location = new Point(6, 571);
        chkHidden.Name = "chkHidden";
        chkHidden.Size = new Size(140, 23);
        chkHidden.TabIndex = 1;
        chkHidden.Text = "Show hidden devices";
        chkHidden.UseVisualStyleBackColor = true;
        // 
        // lblText
        // 
        lblText.Anchor = AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
        lblText.AutoEllipsis = true;
        lblText.ForeColor = SystemColors.HotTrack;
        lblText.Location = new Point(144, 575);
        lblText.Name = "lblText";
        lblText.Size = new Size(262, 16);
        lblText.TabIndex = 1;
        lblText.TextAlign = ContentAlignment.TopCenter;
        // 
        // tabDevices
        // 
        Controls.Add(lblText);
        Controls.Add(chkHidden);
        Controls.Add(btnRefresh);
        Controls.Add(tv);
        Name = "tabDevices";
        Size = new Size(600, 600);

        ResumeLayout(false);
    }
    private void InitializeHandlers() {
        tv.NodeMouseDoubleClick += OnTreeViewNodeMouseDoubleClick;

        btnRefresh.Click += OnButtonClicked;
        chkHidden.Click += OnButtonClicked;
    }

    private void OnTreeViewNodeMouseDoubleClick(object? sender, TreeNodeMouseClickEventArgs e) {
        BeginInvoke(Feature_Properties);
    }

    private void OnButtonClicked(object? sender, EventArgs e) {
        if (sender == null) return;
        if (sender == btnRefresh) { Feature_Refresh(); tv.Focus(); return; }
        if (sender == chkHidden) { Feature_Refresh(); tv.Focus(); return; }
    }

    public void Feature_Refresh() {
        ValidateSelectedNode(out TaskManagerDevice? device);
        PopulateDevices(device);
        Shared.SetStatusText("Devices Refreshed...");
        ForceRefreshClicked?.Invoke(this, EventArgs.Empty);
    }

    public void Feature_Properties() {
        if (!ValidateSelectedNode(out TaskManagerDevice? device) || device == null) { return; }
        if (string.IsNullOrEmpty(device.InstanceID)) return;
        Process.Start("rundll32.exe", $"devmgr.dll,DeviceProperties_RunDLL /DeviceID {device.InstanceID}");
    }

    private bool ValidateSelectedNode(out TaskManagerDevice? device) {
        if (tv.SelectedNode == null || tv.SelectedNode.Level != 1) { device = null; return false; }
        if (tv.SelectedNode.Tag == null) { device = null; return false; }
        device = (TaskManagerDevice)tv.SelectedNode.Tag;
        if (string.IsNullOrEmpty(device.InstanceID)) { device = null; return false; }
        return true;
    }
    private void PopulateDevices(TaskManagerDevice? selectDevice = null) {
        tv.BeginUpdate();
        tv.Nodes.Clear();
        var classes = chkHidden.Checked ? 
            TaskManagerDeviceClass.Load(TaskManagerDeviceFilter.AllClasses, ref il) : 
            TaskManagerDeviceClass.Load(TaskManagerDeviceFilter.AllClasses | TaskManagerDeviceFilter.Present, ref il);

        int _totalDevices = 0;
        int _totalDisabled = 0;
        int _totalDisconnected = 0;
        foreach (var cls in classes) {
            var classNode = tv.Nodes.Add(cls.Description);
            var imgKey = cls.ClassId.ToString();
            if (!il.Images.ContainsKey(imgKey)) { PopulateIconToImageList(ref il, imgKey, cls.IconPath); }
            if (il.Images.ContainsKey(imgKey)) { classNode.ImageKey = imgKey; classNode.SelectedImageKey = imgKey; }
            foreach (var device in cls.Devices) {
                _totalDevices++;
                var deviceNode = classNode.Nodes.Add(device.Name);
                deviceNode.Tag = device;
                if (!device.Present) {
                    deviceNode.NodeFont = new Font(tv.Font, FontStyle.Italic);
                    deviceNode.ForeColor = SystemColors.GrayText;
                    _totalDisconnected++;
                }
                if (device.Disabled) {
                    deviceNode.NodeFont = new Font(tv.Font, FontStyle.Bold);
                    _totalDisabled++;
                }
                if (il.Images.ContainsKey(device.ImageKey)) {
                    deviceNode.ImageKey = device.ImageKey;
                    deviceNode.SelectedImageKey = device.ImageKey;
                } else if (il.Images.ContainsKey(imgKey)) {
                    deviceNode.ImageKey = imgKey;
                    deviceNode.SelectedImageKey = imgKey;
                } else {
                    deviceNode.ImageKey = "";
                    deviceNode.SelectedImageKey = "";
                }
                if (selectDevice != null && selectDevice.InstanceID == device.InstanceID) {
                    tv.SelectedNode = deviceNode;
                }
            }
            tv.Refresh();
        }
        tv.EndUpdate();
        lblText.Text = string.Format("Total: {0}, Disabled: {1}" + (chkHidden.Checked ? ", Disconnected: {2}" : ""), _totalDevices, _totalDisabled, _totalDisconnected);
    }
    private static void PopulateIconToImageList(ref ImageList il, string imgKey, string iconPath) {
        il ??= new ImageList();
        if (il.Images.ContainsKey(imgKey)) return;
        try
        {
            var iconFile = Environment.ExpandEnvironmentVariables(iconPath[..iconPath.IndexOf(",")].Trim());
            var iconIndex = int.Parse(iconPath[(iconPath.IndexOf(",") + 1)..].Trim());
            if (!File.Exists(iconFile)) return;
            IntPtr[] IconPtr = new IntPtr[1];
            if (API.ExtractIconEx(iconFile, iconIndex, null, IconPtr, 1) > 0 && IconPtr[0] > 0)
            {
                il.Images.Add(imgKey, Icon.FromHandle(IconPtr[0]));
                API.DestroyIcon(IconPtr[0]);
            }
            if (il.Images.ContainsKey(imgKey)) return;
            if (iconIndex == -1)
            {
                iconIndex = 0;
                if (API.ExtractIconEx(iconFile, iconIndex, null, IconPtr, 1) > 0 && IconPtr[0] > 0)
                {
                    il.Images.Add(imgKey, Icon.FromHandle(IconPtr[0]));
                    API.DestroyIcon(IconPtr[0]);
                }
            }
            if (il.Images.ContainsKey(imgKey)) return;
            Debug.WriteLine($"Failed to PopulateIconToImageList: {iconFile} - {iconIndex}");
        }
        catch
        {
        }
        finally
        {
            if (!il.Images.ContainsKey(imgKey)) { il.Images.Add(imgKey, new Bitmap(16, 16)); }
        }
    }

    public sMkListView? ListView => null;
    public string Title { get; set; } = "Devices";
    public string Description { get; set; } = "Device Manager";
    public string TimmingKey => string.Empty;
    public long TimmingValue => 0;
    public bool CanSelectColumns => false;
    public void ForceRefresh() => Feature_Refresh();
    public TaskManagerColumnTypes ColumnType => TaskManagerColumnTypes.None;

    private void RefresherDoWork(bool firstTime = false) {
        if (tv.Nodes.Count == 0) firstTime = true;
        if (firstTime) {
            RefreshStarts?.Invoke(this, EventArgs.Empty);
            PopulateDevices();
            RefreshComplete?.Invoke(this, EventArgs.Empty);
        }
    }
    public void Refresher(bool firstTime = false) {
        if (Visible || firstTime) {
            if (InvokeRequired) {
                Invoke(() => RefresherDoWork(firstTime));
            } else {
                RefresherDoWork(firstTime);
            }
        }
    }

}
