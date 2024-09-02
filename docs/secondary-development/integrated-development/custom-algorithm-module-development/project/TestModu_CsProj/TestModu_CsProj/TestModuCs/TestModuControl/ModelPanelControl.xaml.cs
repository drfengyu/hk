using Apps.Data;
using Apps.XmlParser.ParamTab;
using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using VMControls.BaseInterface;

namespace TestModuControl
{
    /// <summary>
    /// ModelPanel.xaml 的交互逻辑
    /// </summary>
    public partial class ModelPanelControl : UserControl
    {
        public Tab TabSource
        {
            get { return (Tab)GetValue(TabSourceProperty); }
            set { SetValue(TabSourceProperty, value); }
        }

        public static readonly DependencyProperty TabSourceProperty =
            DependencyProperty.Register("TabSource", typeof(Tab), typeof(ModelPanelControl), new PropertyMetadata(null));

        public object ParentNode
        {
            get { return (object)GetValue(ParentNodeProperty); }
            set { SetValue(ParentNodeProperty, value); }
        }

        public static readonly DependencyProperty ParentNodeProperty =
            DependencyProperty.Register("ParentNode", typeof(object), typeof(ModelPanelControl), new PropertyMetadata(null));

        public bool ModelExist
        {
            get { return (bool)GetValue(ModelExistProperty); }
            set { SetValue(ModelExistProperty, value); }
        }

        public static readonly DependencyProperty ModelExistProperty =
            DependencyProperty.Register("ModelExist", typeof(bool), typeof(ModelPanelControl), new PropertyMetadata(false));

        private IParamsConfig ownerModuleParam = null;
        /// <summary>
        /// 所属模块参数通信接口
        /// </summary>
        public IParamsConfig OwnerModuleParam
        {
            get
            {
                if (ownerModuleParam == null)
                {
                    if (ParentNode is NameValueItem parent)
                    {
                        var root = parent.GetTopBaseNode() as AlgorithmTabRoot;
                        if (root != null)
                        {
                            ownerModuleParam = root.UserStringData;
                        }
                    }
                }
                return ownerModuleParam;
            }
        }

        public ModelPanelControl()
        {
            InitializeComponent();
        }

        private void BtnNewModel_Click(object sender, RoutedEventArgs e)
        {
            ModelConfigDialog modelConfigDialog = new ModelConfigDialog();
            PopDialog(modelConfigDialog);
        }

        HikPcUI.ImageView.Byte2ImageSource b2SConvertor = new HikPcUI.ImageView.Byte2ImageSource();
        private void RefreshModelImage(ModelData model)
        {
            try
            {
                ModelPanel.GetModel(OwnerModuleParam, model);
                if (model.ImageBuffer == null)
                {
                    return;
                }
            }
            catch (Exception)
            {
                return;
            }
            
            ModelExist = true;

            try
            {
                ImageData ModelImage = model.ModelImageData;
                if (ModelImage == null)
                {
                    ModelPanel.CreateModelImageData(model);
                    ModelImage = model.ModelImageData;
                }
                if (ModelImage != null)
                {
                    imgModel.Source = b2SConvertor.BuiltImageSource(ModelImage.ImageBuffer, ModelImage.Width, ModelImage.Height, ModelImage.PixelFormat);
                }
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        private void BtnEditModel_Click(object sender, RoutedEventArgs e)
        {
            ModelConfigDialog modelConfigDialog = new ModelConfigDialog(true);
            PopDialog(modelConfigDialog);
        }

        private void PopDialog(ModelConfigDialog modelConfigDialog)
        {
            Binding binding = new Binding("TabSource") { Source = this };
            modelConfigDialog.SetBinding(ModelConfigDialog.ParamSourceProperty, binding);
            modelConfigDialog.ModuleParam = OwnerModuleParam;
            if (modelConfigDialog.ShowDialog() == true)
            {
                ModelData model = new ModelData();
                try
                {
                    RefreshModelImage(model);
                }
                catch (System.Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
        }

        private void Import_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog openFileDialog = new Microsoft.Win32.OpenFileDialog();
            openFileDialog.Filter = "xml files(*.xml)|*.xml";

            string fPath = string.Empty;
            Nullable<bool> result = openFileDialog.ShowDialog();
            if (result == true)
            {
                fPath = openFileDialog.FileName;
                LoadModelByPath(fPath);
            }
        }

        private void LoadModelByPath(string path)
        {
            if (string.IsNullOrEmpty(path))
            {
                return;
            }
            ModelData modelData = new ModelData();

            try
            {
                //加载xml
                modelData.loadXml(path);
                if (modelData.ImageBuffer == null)
                {
                    throw new System.Exception("ImageData is null.");
                }

                ModelPanel.CreateModel(OwnerModuleParam, modelData);
                RefreshModelImage(modelData);
            }
            catch
            {
                MessageBox.Show("导入失败");
            }
        }

        private void Export_Click(object sender, RoutedEventArgs e)
        {
            ModelData model = new ModelData();
            try
            {
                Microsoft.Win32.SaveFileDialog saveFileDialog = new Microsoft.Win32.SaveFileDialog();
                saveFileDialog.Filter = "xml files(*.xml)|*.xml";

                //保存对话框是否记忆上次打开的目录 
                saveFileDialog.RestoreDirectory = true;
                string initpath = string.Empty;
                Nullable<bool> result = saveFileDialog.ShowDialog();
                if (result == true)
                {
                    ModelPanel.GetModel(OwnerModuleParam, model);
                    model.Save(saveFileDialog.FileName);

                    MessageBox.Show("保存成功");
                }
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void UserControl_Loaded(object sender, RoutedEventArgs e)
        {
            ModelData model = new ModelData();
            try
            {
                RefreshModelImage(model);
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
    }

}
