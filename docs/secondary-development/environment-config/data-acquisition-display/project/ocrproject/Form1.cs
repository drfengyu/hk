using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using VM.Core;
using VM.PlatformSDKCS;
using VMControls.Winform.Release;

namespace ocrproject
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            KillProcess("VisionMasterServerApp");
            KillProcess("VisionMaster");
            KillProcess("VmModuleProxy.exe");
            InitializeComponent();
            //注册回调函数,推荐回调函数获取结果.
            VmSolution.OnWorkStatusEvent += VmSolution_OnWorkStatusEvent;
            
        }

        private void VmSolution_OnWorkStatusEvent(ImvsSdkDefine.IMVS_MODULE_WORK_STAUS workStatusInfo)
        {
            try
            {
                if (workStatusInfo.nWorkStatus==0 && workStatusInfo.nProcessID==10000)//为0表示执行完毕,为1表示正在执行,10000表示流程1
                {
                    //通过流程获取结果,分为渲染结果和数据结果

                    VmProcedure vmProcedure = (VmProcedure)VmSolution.Instance["流程1"];
                    string ocrResult = vmProcedure.ModuResult.GetOutputString("out").astStringVal[0].strValue;
                    string ocrNum = vmProcedure.ModuResult.GetOutputInt("out0").pIntVal[0].ToString();
                    this.BeginInvoke(new Action(() => {//回调里对控件操作需要使用委托
                        vmRenderControl1.ModuleSource = vmProcedure;//渲染结果
                        listBox1.Items.Add("字符识别结果:" + ocrResult);
                        listBox1.TopIndex = listBox1.Items.Count - 1;
                        listBox1.Items.Add("个数:" + ocrNum);
                        listBox1.TopIndex = listBox1.Items.Count - 1;
                    }));

                    //通过模块获取结果
                    IMVSOcrModuCs.IMVSOcrModuTool ocrModuTool = (IMVSOcrModuCs.IMVSOcrModuTool)VmSolution.Instance["流程1.字符识别1"];
                    string ocrScore1 = ocrModuTool.ModuResult.CharNum.ToString();

                }
            }
            catch (VmException ex)
            {

                MessageBox.Show(ex.Message);
            }
        }

        private void KillProcess(string strKillName)
        {
            foreach (var item in System.Diagnostics.Process.GetProcesses())
            {
                if (item.ProcessName.Contains(strKillName))
                {
                    try
                    {
                        item.Kill();
                        item.WaitForExit();
                    }
                    catch (Exception ex)
                    {

                        Console.WriteLine(ex.Message);
                    }
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog fileDialog = new OpenFileDialog();
            fileDialog.Filter = "VM Sol File|*.sol*";
            if (fileDialog.ShowDialog()==DialogResult.OK)
            {
                textBox1.Text = fileDialog.FileName;
            }
            listBox1.Items.Add("添加路径成功.");
            listBox1.TopIndex = listBox1.Items.Count - 1;
        }

        private void button4_Click(object sender, EventArgs e)
        {
            try
            {
                VmSolution.Load(textBox1.Text);
                listBox1.Items.Add("方案加载成功.");
                listBox1.TopIndex = listBox1.Items.Count - 1;
            }
            catch (VmException ex)
            {

                MessageBox.Show("VM SDK异常:" + Convert.ToString(ex.errorCode, 16));
            }
            catch (Exception ex) {
                MessageBox.Show("系统异常:"+ex.Message);
            }
            
        }
        VmParamsConfigWithRenderControl vmParamsConfigWithRenderControl1 { set; get; }
        /// <summary>
        /// 方案执行
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button3_Click(object sender, EventArgs e)
        {
            try
            {
                //模块的参数配置
                groupBox5.Controls.Clear();
                IMVSOcrModuCs.IMVSOcrModuTool ocrTool = (IMVSOcrModuCs.IMVSOcrModuTool)VmSolution.Instance["流程1.字符识别1"];
                vmParamsConfigWithRenderControl1 = new VmParamsConfigWithRenderControl();
                vmParamsConfigWithRenderControl1.Dock = DockStyle.Fill;
                vmParamsConfigWithRenderControl1.ModuleSource = ocrTool;
                groupBox5.Controls.Add(vmParamsConfigWithRenderControl1);

                VmSolution.Instance.SyncRun();
                listBox1.Items.Add("方案运行成功.");
                listBox1.TopIndex = listBox1.Items.Count - 1;

                //添加全局工具控件
                groupBox7.Controls.Clear();
                VmGlobalToolControl globalToolControl = new VmGlobalToolControl();
                globalToolControl.Dock = DockStyle.Fill;
                groupBox7.Controls.Add(globalToolControl);
                
            }
            catch (VmException ex)
            {

                MessageBox.Show(ex.Message);
            }
            

        }

        private void button2_Click(object sender, EventArgs e)
        {
            VmSolution.Save();
            listBox1.Items.Add("方案保存成功.");
            listBox1.TopIndex = listBox1.Items.Count - 1;
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            VmSolution.Instance.Dispose();
        }
        /// <summary>
        /// 下拉获取所有流程
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void comboBox1_DropDown(object sender, EventArgs e)
        {
            try
            {
                ProcessInfoList processInfoList = VmSolution.Instance.GetAllProcedureList();
                comboBox1.Items.Clear();
                for (int i = 0; i < processInfoList.nNum; i++)
                {
                    comboBox1.Items.Add(processInfoList.astProcessInfo[i].strProcessName);
                }
            }
            catch (VmException ex)
            {

                MessageBox.Show(Convert.ToString(ex.errorCode,16));
            }
        }
        /// <summary>
        /// 流程区绑定单个流程
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button5_Click(object sender, EventArgs e)
        {
            try
            {
                vmProcedureConfigControl1.BindSingleProcedure(comboBox1.Text);
            }
            catch (VmException ex)
            {

                MessageBox.Show(Convert.ToString(ex.errorCode,16));
            }
        }
        /// <summary>
        /// 流程区绑定多个流程
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button6_Click(object sender, EventArgs e)
        {
            try
            {
                vmProcedureConfigControl1.BindMultiProcedure();
            }
            catch (VmException ex)
            {

                MessageBox.Show(Convert.ToString(ex.errorCode,16));
            }
        }


        /// <summary>
        /// 选择流程路径
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button7_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "VM Prc Files|*.prc*";
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                RunTryCatch(() =>
                {
                    textBox2.Text = openFileDialog.FileName;
                }, "流程选择路径成功.");
            }
        }
        /// <summary>
        /// 导入流程
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button11_Click(object sender, EventArgs e)
        {
            RunTryCatch(() => {VmProcedure.Load(textBox2.Text, "");},
                "流程导入成功.");
        }
        /// <summary>
        /// 导出流程
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button10_Click(object sender, EventArgs e)
        {
            RunTryCatch(() => {VmProcedure vmProcedure = (VmProcedure)VmSolution.Instance[comboBox1.Text];vmProcedure.SaveAs(Path.Combine(AppDomain.CurrentDomain.BaseDirectory,"流程导出测试.prc"));}, 
                "流程导出成功.");
        }
        /// <summary>
        /// 运行流程
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button8_Click(object sender, EventArgs e)
        {
            RunTryCatch(() => {VmProcedure vmProcedure = (VmProcedure)VmSolution.Instance[comboBox1.Text];vmProcedure.Run();/*vmProcedure.ContinuousRunEnable = true;流程连续运行*/},
                $"运行一次流程{comboBox1.Text}成功.");
        }
        /// <summary>
        /// 流程删除
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button9_Click(object sender, EventArgs e)
        {
            RunTryCatch(() => { VmSolution.Instance.DeleteOneProcedure(comboBox1.Text); }, "流程删除成功.");
        }
        /// <summary>
        /// 消息显示区显示消息
        /// </summary>
        /// <param name="msg"></param>
        public void AddMsg(string msg) {
            if (!string.IsNullOrEmpty(msg))
            {
                listBox1.Items.Add(msg);
                listBox1.TopIndex = listBox1.Items.Count - 1;
            }
        }
        /// <summary>
        /// TryCatch捕获SDK异常,系统异常
        /// </summary>
        /// <param name="excute"></param>
        /// <param name="msg"></param>
        public void RunTryCatch(Action excute,string msg) {
            try
            {
                excute();
                AddMsg(msg);
            }
            catch (VmException ex)
            {
                MessageBox.Show(Convert.ToString(ex.errorCode, 16));
            }
            catch (Exception ex) {
                MessageBox.Show(ex.Message);
            }
        }

        /// <summary>
        /// 模块列表获取
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void comboBox2_DropDown(object sender, EventArgs e)
        {
            RunTryCatch(() => {
                VmProcedure vmProcedure = (VmProcedure)VmSolution.Instance[comboBox1.Text];
                comboBox2.Items.Clear();
                ModuleInfoList moduleInfoList = vmProcedure.GetAllModuleList();
                for (int i = 0; i < moduleInfoList.nNum; i++)
                {
                    comboBox2.Items.Add(moduleInfoList.astModuleInfo[i].strDisplayName);
                }
            },"模块列表获取成功.");
            
        }
        /// <summary>
        /// 动态绑定模块进行参数配置
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button12_Click(object sender, EventArgs e)
        {
            RunTryCatch(() => {
                VmModule vmModule = (VmModule)VmSolution.Instance[comboBox1.Text+"."+ comboBox2.Text];
                vmParamsConfigWithRenderControl1.ModuleSource = vmModule;
            },"模块绑定成功.");
           
        }


    }
}
