"use strict";(self.webpackChunkmy_website=self.webpackChunkmy_website||[]).push([[4],{65657:(n,e,r)=>{r.r(e),r.d(e,{assets:()=>a,contentTitle:()=>d,default:()=>u,frontMatter:()=>s,metadata:()=>l,toc:()=>c});var o=r(74848),t=r(28453),i=r(49677);const s={sidebar_position:4},d="\u53c2\u6570\u6a21\u5757\u914d\u7f6e",l={id:"secondary-development/environment-config/module-parameter-configuration/index",title:"\u53c2\u6570\u6a21\u5757\u914d\u7f6e",description:"\u53c2\u6570\u914d\u7f6e\u63a7\u4ef6",source:"@site/docs/secondary-development/environment-config/module-parameter-configuration/index.md",sourceDirName:"secondary-development/environment-config/module-parameter-configuration",slug:"/secondary-development/environment-config/module-parameter-configuration/",permalink:"/hk/docs/secondary-development/environment-config/module-parameter-configuration/",draft:!1,unlisted:!1,editUrl:"https://github.com/drfengyu/hk/tree/gh-pages/docs/secondary-development/environment-config/module-parameter-configuration/index.md",tags:[],version:"current",sidebarPosition:4,frontMatter:{sidebar_position:4},sidebar:"tutorialSidebar",previous:{title:"\u6e32\u67d3\u53ca\u6570\u636e\u7ed3\u679c\u83b7\u53d6",permalink:"/hk/docs/secondary-development/environment-config/data-acquisition-display/"},next:{title:"\u5c0f\u6280\u5de7",permalink:"/hk/docs/secondary-development/environment-config/small-skill/"}},a={},c=[{value:"\u53c2\u6570\u914d\u7f6e\u63a7\u4ef6",id:"\u53c2\u6570\u914d\u7f6e\u63a7\u4ef6",level:2},{value:"1. VmParamsConfigWithRenderControl",id:"1-vmparamsconfigwithrendercontrol",level:3},{value:"2. VmParamsConfigControl",id:"2-vmparamsconfigcontrol",level:3}];function m(n){const e={code:"code",h1:"h1",h2:"h2",h3:"h3",header:"header",img:"img",li:"li",ol:"ol",p:"p",pre:"pre",ul:"ul",...(0,t.R)(),...n.components};return(0,o.jsxs)(o.Fragment,{children:[(0,o.jsx)(e.header,{children:(0,o.jsx)(e.h1,{id:"\u53c2\u6570\u6a21\u5757\u914d\u7f6e",children:"\u53c2\u6570\u6a21\u5757\u914d\u7f6e"})}),"\n","\n",(0,o.jsx)(i.A,{src:"https://xian-vforum.oss-cn-hangzhou.aliyuncs.com/2022-07-04_f9KiRjrJqD_1.4%E6%A8%A1%E5%9D%97%E5%8F%82%E6%95%B0%E9%85%8D%E7%BD%AE_x264.mp4"}),"\n",(0,o.jsx)(e.h2,{id:"\u53c2\u6570\u914d\u7f6e\u63a7\u4ef6",children:"\u53c2\u6570\u914d\u7f6e\u63a7\u4ef6"}),"\n",(0,o.jsx)(e.p,{children:"\u5de5\u5177\u7bb1\u4e2d\u63d0\u4f9b\u4e86\u4e24\u4e2a\u53c2\u6570\u914d\u7f6e\u63a7\u4ef6."}),"\n",(0,o.jsxs)(e.ul,{children:["\n",(0,o.jsx)(e.li,{children:"VmParamsConfigControl\u662f\u4e0d\u5e26\u6e32\u67d3\u7684\u53c2\u6570\u914d\u7f6e\u63a7\u4ef6."}),"\n",(0,o.jsx)(e.li,{children:"VmParamsConfigWithRenderControl\u662f\u5e26\u6e32\u67d3\u7684\u53c2\u6570\u914d\u7f6e\u63a7\u4ef6."}),"\n"]}),"\n",(0,o.jsx)(e.h3,{id:"1-vmparamsconfigwithrendercontrol",children:"1. VmParamsConfigWithRenderControl"}),"\n",(0,o.jsxs)(e.ol,{children:["\n",(0,o.jsx)(e.li,{children:"\u914d\u7f6e\u6a21\u5757\u6570\u636e\u6e90"}),"\n"]}),"\n",(0,o.jsx)(e.pre,{children:(0,o.jsx)(e.code,{className:"language-Csharp",children:'        private void button3_Click(object sender, EventArgs e)\r\n        {\r\n            //\u6a21\u5757\u7684\u53c2\u6570\u914d\u7f6e\r\n           \r\n            IMVSOcrModuCs.IMVSOcrModuTool ocrTool = (IMVSOcrModuCs.IMVSOcrModuTool)VmSolution.Instance["\u6d41\u7a0b1.\u5b57\u7b26\u8bc6\u522b1"];\r\n            VmParamsConfigWithRenderControl vmParamsConfigWithRenderControl1 = new VmParamsConfigWithRenderControl();\r\n            vmParamsConfigWithRenderControl1.Dock = DockStyle.Fill;\r\n            vmParamsConfigWithRenderControl1.ModuleSource = ocrTool;\r\n            groupBox5.Controls.Add(vmParamsConfigWithRenderControl1);\r\n\r\n            VmSolution.Instance.SyncRun();\r\n            listBox1.Items.Add("\u65b9\u6848\u8fd0\u884c\u6210\u529f.");\r\n            listBox1.TopIndex = listBox1.Items.Count - 1;\r\n\r\n            //\u83b7\u53d6\u7ed3\u679c,\u5206\u4e3a\u6e32\u67d3\u7ed3\u679c\u548c\u6570\u636e\u7ed3\u679c\r\n\r\n            VmProcedure vmProcedure = (VmProcedure)VmSolution.Instance["\u6d41\u7a0b1"];\r\n\r\n            vmRenderControl1.ModuleSource = vmProcedure;\r\n\r\n            string ocrResult = vmProcedure.ModuResult.GetOutputString("out").astStringVal[0].strValue;\r\n            string ocrNum = vmProcedure.ModuResult.GetOutputInt("out0").pIntVal[0].ToString();\r\n\r\n            listBox1.Items.Add("\u5b57\u7b26\u8bc6\u522b\u7ed3\u679c:"+ocrResult);\r\n            listBox1.TopIndex = listBox1.Items.Count - 1;\r\n            listBox1.Items.Add("\u4e2a\u6570:" + ocrNum);\r\n            listBox1.TopIndex = listBox1.Items.Count - 1;\r\n\r\n        }\n'})}),"\n",(0,o.jsxs)(e.ol,{start:"3",children:["\n",(0,o.jsx)(e.li,{children:"\u70b9\u51fb\u65b9\u6848\u6267\u884c\u9a8c\u8bc1\u6548\u679c"}),"\n"]}),"\n",(0,o.jsx)(e.p,{children:(0,o.jsx)(e.img,{src:r(41717).A+"",width:"1646",height:"694"})}),"\n",(0,o.jsx)(e.p,{children:(0,o.jsx)(e.img,{src:r(58828).A+"",width:"1436",height:"559"})}),"\n",(0,o.jsx)(e.h3,{id:"2-vmparamsconfigcontrol",children:"2. VmParamsConfigControl"}),"\n",(0,o.jsx)(e.p,{children:"\u4e0e\u4e0a\u8ff0\u7c7b\u4f3c,\u53ea\u662f\u53c2\u6570\u914d\u7f6e\u63a7\u4ef6\u4e0d\u5e26\u53f3\u4fa7\u56fe\u50cf\u6e32\u67d3."}),"\n",(0,o.jsx)(e.pre,{children:(0,o.jsx)(e.code,{className:"language-Csharp",children:"vmParamsConfigControl1.ModuleSource = ocrTool;\n"})})]})}function u(n={}){const{wrapper:e}={...(0,t.R)(),...n.components};return e?(0,o.jsx)(e,{...n,children:(0,o.jsx)(m,{...n})}):m(n)}},41717:(n,e,r)=>{r.d(e,{A:()=>o});const o=r.p+"assets/images/image-2-af2c9635b1d4771f2db1e2c1d8da6af1.png"},58828:(n,e,r)=>{r.d(e,{A:()=>o});const o=r.p+"assets/images/image-3-80efdc953507b35c1dcd92b9702e9d6e.png"}}]);