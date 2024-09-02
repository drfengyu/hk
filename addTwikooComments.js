const fs = require('fs');
const path = require('path');

// 定义要处理的目录
const docsDir = path.join(__dirname, 'docs');
console.log(`Processing files in directory: ${docsDir}`); // 调试信息

// 定义要添加的内容

const importStatement = "";
const componentUsage = "";

// 递归读取目录
function processDirectory(directory) {
  fs.readdir(directory, { withFileTypes: true }, (err, files) => {
    if (err) {
      return console.error('读取目录失败', err);
    }

    files.forEach(file => {
      const filePath = path.join(directory, file.name);

      if (file.isDirectory()) {
        // 如果是目录，递归处理
        processDirectory(filePath);
      } else if (path.extname(file.name) === '.md') {
        // 只处理 .md 文件
        fs.readFile(filePath, 'utf8', (err, data) => {
          if (err) {
            return console.error('读取文件失败', err);
          }

          // 检查是否已经添加
          if (data.includes(importStatement)) {
            console.log(`文件 ${filePath} 已经包含 TwikooComment 组件。`);
            return; // 如果已经添加，则跳过
          }

          // 在文件末尾添加内容
          const updatedData = `${data}\n\n${importStatement}\n${componentUsage}\n`;
          
          fs.writeFile(filePath, updatedData, 'utf8', err => {
            if (err) {
              return console.error('写入文件失败', err);
            }
            console.log(`已更新文件: ${filePath}`);
          });
        });
      }
    });
  });
}

// 开始处理 docs 目录
processDirectory(docsDir);
