using System.ComponentModel;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Runtime.Versioning;
using System.Security.Principal;
using sMkTaskManager.Classes;
using sMkTaskManager.Controls;
namespace sMkTaskManager.Forms;

[DesignerCategory("Component"), SupportedOSPlatform("windows")]
internal class tabDevices : UserControl, ITaskManagerTab {
    private ImageList il;
    private TreeView tv;
    private Label lblText;
    private Button btnForceRefresh;
    private Button btnProperties;
    private CheckBox chkHidden;
    private ContextMenuStrip cms;
    private ToolStripMenuItem cmsRefresh;
    private ToolStripMenuItem cmsEnable;
    private ToolStripMenuItem cmsDisable;
    private ToolStripMenuItem cmsUninstall;
    private ToolStripMenuItem cmsProperties;
    private ToolStripSeparator cmsSeparator1;
    private ToolStripSeparator cmsSeparator2;

    public event EventHandler? RefreshStarts;
    public event EventHandler? RefreshComplete;
    public event EventHandler? ForceRefreshClicked;

    private IContainer? components = null;
    protected override void Dispose(bool disposing) {
        if (disposing && (components != null)) { components.Dispose(); }
        base.Dispose(disposing);
    }

    public tabDevices() {
        InitializeComponent();
        InitializeHandlers();
        InitializeExtras();
    }
    private void InitializeComponent() {
        components = new Container();
        tv = new TreeView();
        cms = new ContextMenuStrip(components);
        cmsRefresh = new ToolStripMenuItem();
        cmsSeparator1 = new ToolStripSeparator();
        cmsEnable = new ToolStripMenuItem();
        cmsDisable = new ToolStripMenuItem();
        cmsUninstall = new ToolStripMenuItem();
        cmsSeparator2 = new ToolStripSeparator();
        cmsProperties = new ToolStripMenuItem();
        il = new ImageList(components);
        btnForceRefresh = new Button();
        btnProperties = new Button();
        chkHidden = new CheckBox();
        lblText = new Label();
        cms.SuspendLayout();
        SuspendLayout();
        // 
        // tv
        // 
        tv.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
        tv.BorderStyle = BorderStyle.FixedSingle;
        tv.ContextMenuStrip = cms;
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
        // cms
        // 
        cms.Items.AddRange(new ToolStripItem[] { cmsRefresh, cmsSeparator1, cmsEnable, cmsDisable, cmsUninstall, cmsSeparator2, cmsProperties });
        cms.Name = "cms";
        cms.Size = new Size(158, 176);
        // 
        // cmsRefresh
        // 
        cmsRefresh.Name = "cmsRefresh";
        cmsRefresh.Size = new Size(157, 22);
        cmsRefresh.Text = "&Refresh";
        // 
        // cmsSeparator1
        // 
        cmsSeparator1.Name = "cmsSeparator1";
        cmsSeparator1.Size = new Size(154, 6);
        // 
        // cmsEnable
        // 
        cmsEnable.Name = "cmsEnable";
        cmsEnable.Size = new Size(157, 22);
        cmsEnable.Text = "&Enable device";
        // 
        // cmsDisable
        // 
        cmsDisable.Name = "cmsDisable";
        cmsDisable.Size = new Size(157, 22);
        cmsDisable.Text = "&Disable device";
        // 
        // cmsUninstall
        // 
        cmsUninstall.Name = "cmsUninstall";
        cmsUninstall.Size = new Size(157, 22);
        cmsUninstall.Text = "&Uninstall device";
        // 
        // cmsSeparator2
        // 
        cmsSeparator2.Name = "cmsSeparator2";
        cmsSeparator2.Size = new Size(154, 6);
        // 
        // cmsProperties
        // 
        cmsProperties.Name = "cmsProperties";
        cmsProperties.Size = new Size(157, 22);
        cmsProperties.Text = "&Properties";
        // 
        // il
        // 
        il.ColorDepth = ColorDepth.Depth32Bit;
        il.ImageSize = new Size(16, 16);
        il.TransparentColor = Color.Transparent;
        // 
        // btnForceRefresh
        // 
        btnForceRefresh.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;
        btnForceRefresh.Location = new Point(505, 571);
        btnForceRefresh.Margin = new Padding(0, 3, 3, 3);
        btnForceRefresh.Name = "btnForceRefresh";
        btnForceRefresh.Size = new Size(89, 23);
        btnForceRefresh.TabIndex = 3;
        btnForceRefresh.Text = "Force Refresh";
        btnForceRefresh.UseVisualStyleBackColor = true;
        // 
        // btnProperties
        // 
        btnProperties.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;
        btnProperties.Location = new Point(413, 571);
        btnProperties.Margin = new Padding(0, 3, 3, 3);
        btnProperties.Name = "btnProperties";
        btnProperties.Size = new Size(89, 23);
        btnProperties.TabIndex = 2;
        btnProperties.Text = "Properties";
        btnProperties.UseVisualStyleBackColor = true;
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
        Controls.Add(btnProperties);
        Controls.Add(btnForceRefresh);
        Controls.Add(tv);
        Name = "tabDevices";
        Size = new Size(600, 600);
        cms.ResumeLayout(false);
        ResumeLayout(false);
    }
    private void InitializeHandlers() {
        VisibleChanged += OnVisibleChanged;
        tv.AfterSelect += OnTreeViewAfterSelect;
        tv.NodeMouseClick += OnTreeViewNodeMouseClick;
        tv.NodeMouseDoubleClick += OnTreeViewNodeMouseDoubleClick;
        cms.Opening += OnContextOpening;
        cms.ItemClicked += OnContextItemClicked;
        btnProperties.Click += OnButtonClicked;
        btnForceRefresh.Click += OnButtonClicked;
        chkHidden.Click += OnButtonClicked;
    }
    private void InitializeExtras() {
        il.Images.Clear();
        il.Images.Add("", new Bitmap(16, 16));
        cmsProperties.SwitchToBold();
        btnProperties.Enabled = false;
    }

    private void OnVisibleChanged(object? sender, EventArgs e) {
        if (Visible && tv.Nodes.Count == 0 && Shared.InitComplete) {
            Refresher(true);
        }
    }
    private void OnTreeViewAfterSelect(object? sender, TreeViewEventArgs e) {
        ValidateSelectedNode(out TaskManagerDevice? device);
        btnProperties.Enabled = device != null;
    }
    private void OnTreeViewNodeMouseClick(object? sender, TreeNodeMouseClickEventArgs e) {
        if (e.Button == MouseButtons.Right && e.Node != null) {
            tv.SelectedNode = e.Node;
        }
    }
    private void OnTreeViewNodeMouseDoubleClick(object? sender, TreeNodeMouseClickEventArgs e) {
        BeginInvoke(Feature_Properties);
    }
    private void OnContextOpening(object? sender, CancelEventArgs e) {
        if (tv.SelectedNode == null || tv.SelectedNode.Level != 1) { e.Cancel = true; return; }
        if (tv.SelectedNode.Tag == null) { e.Cancel = true; return; }
        var device = (TaskManagerDevice)tv.SelectedNode.Tag;

        cmsEnable.Enabled = device.Disabled && device.Present;
        cmsDisable.Enabled = !device.Disabled && device.Present;
        cmsEnable.Visible = cmsEnable.Enabled;
        cmsDisable.Visible = cmsDisable.Enabled;
    }

    private void OnContextItemClicked(object? sender, ToolStripItemClickedEventArgs e) {
        if (e.ClickedItem == null) return;
        if (!e.ClickedItem.Enabled) return;
        switch (e.ClickedItem.Name) {
            case nameof(cmsRefresh): { BeginInvoke(Feature_ForceRefresh); break; }
            case nameof(cmsProperties): { BeginInvoke(Feature_Properties); break; }
            case nameof(cmsEnable): { BeginInvoke(Feature_Enable); break; }
            case nameof(cmsDisable): { BeginInvoke(Feature_Disable); break; }
            case nameof(cmsUninstall): { BeginInvoke(Feature_Uninstall); break; }
            default: break;
        }
    }
    private void OnButtonClicked(object? sender, EventArgs e) {
        if (sender == null) return;
        if (sender == btnProperties) { Feature_Properties(); tv.Focus(); return; }
        if (sender == btnForceRefresh) { Feature_ForceRefresh(); tv.Focus(); return; }
        if (sender == chkHidden) { Feature_ForceRefresh(); tv.Focus(); return; }
    }

    public void Feature_ForceRefresh() {
        ValidateSelectedNode(out TaskManagerDevice? device);
        PopulateDevices(device);
        Shared.SetStatusText("Devices Refreshed...");
        ForceRefreshClicked?.Invoke(this, EventArgs.Empty);
    }
    public void Feature_Enable() {
        Feature_EnableDisable(true);
    }
    public void Feature_Disable() {
        Feature_EnableDisable(false);
    }
    public void Feature_EnableDisable(bool enable) {
        if (!ValidateSelectedNode(out TaskManagerDevice? device) || device == null) { return; }
        if (!enable) {
            var msg = MessageBox.Show("Disabling this device will cause it to stop functioning.\r\nDo you really want to disable it?", device.Name, MessageBoxButtons.YesNo, MessageBoxIcon.Warning);
            if (msg != DialogResult.Yes) return;
        }

        var cmStatus = API.CM_Locate_DevNode(out IntPtr pHKey, device.InstanceID, 0); // CM_LOCATE_DEVNODE_NORMAL==0
        if (cmStatus != 0) { Shared.SetStatusText($"Failed to get device handle to change state: {cmStatus}."); return; }
        var result = enable ? API.CM_Enable_DevNode(pHKey, 0) : API.CM_Disable_DevNode(pHKey, 0);
        if (result == 0x00000033) { Debug.WriteLine($"Access denied to change device state: {result}."); return; }
        if (result != 0) { Shared.SetStatusText($"Failed to change device state: {result}."); return; }
        PopulateDevices(device);
        Shared.SetStatusText($"Device {device.Name} {(enable ? "Enabled" : "Disabled")}...");
    }
    public void Feature_Uninstall() {
        if (!ValidateSelectedNode(out TaskManagerDevice? device) || device == null) { return; }
        var msg = MessageBox.Show("Warning\r\nYou are about to uninstall this device form your system.\r\nDo you want to continue?", device.Name, MessageBoxButtons.OKCancel, MessageBoxIcon.Warning);
        if (msg != DialogResult.OK) return;

        var cmStatus = API.CM_Locate_DevNode(out IntPtr pHKey, device.InstanceID, 0); // CM_LOCATE_DEVNODE_NORMAL==0
        if (cmStatus != 0) { Shared.SetStatusText($"Failed to get device handle to uninstall: {cmStatus}."); return; }
        var result = API.CM_Uninstall_DevNode(pHKey, 0);
        if (result != 0) { Shared.SetStatusText($"Failed to uninstall device: {result}."); return; }
        PopulateDevices(device);
        Shared.SetStatusText($"Device {device.Name} uninstalled...");
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
        var classes = chkHidden.Checked ? TaskManagerDeviceClass.Load(TaskManagerDeviceFilter.AllClasses, ref il) : TaskManagerDeviceClass.Load(TaskManagerDeviceFilter.AllClasses | TaskManagerDeviceFilter.Present, ref il);
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
                   // deviceNode.ImageKey = device.ImageKey;
                   // deviceNode.SelectedImageKey = device.ImageKey;
                } else if (il.Images.ContainsKey(imgKey)) {
                   // deviceNode.ImageKey = imgKey;
                  //  deviceNode.SelectedImageKey = imgKey;
                } else {
                   // deviceNode.ImageKey = "";
                   // deviceNode.SelectedImageKey = "";
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
        return;
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
    public void ForceRefresh() => Feature_ForceRefresh();
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
