// src/pages/SubmitPost.js

import React, { useState } from 'react';
import Layout from '@theme/Layout';
import axios from 'axios';
import MarkdownEditor from 'react-markdown-editor-lite';
import 'react-markdown-editor-lite/lib/index.css';
import MarkdownIt from 'markdown-it';
import '@site/src/css/submit-post.css';
const GITHUB_TOKEN = 'YOUR_GITHUB_TOKEN'; // 替换为您的 GitHub 个人访问令牌
const REPO_OWNER = 'YOUR_GITHUB_USERNAME'; // 替换为您的 GitHub 用户名
const REPO_NAME = 'YOUR_REPO_NAME'; // 替换为您的仓库名称
const BRANCH = 'main'; // 替换为您希望提交到的分支

const mdParser = new MarkdownIt();

function SubmitPostForm() {
  const [title, setTitle] = useState('');
  const [authorName, setAuthorName] = useState('');
  const [authorImage, setAuthorImage] = useState('');
  const [tags, setTags] = useState('');
  const [content, setContent] = useState('');
  const [loading, setLoading] = useState(false);
  const [message, setMessage] = useState('');

  const handleEditorChange = ({ text }) => {
    setContent(text);
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    setLoading(true);
    setMessage('');

    const filePath = `blog/${title.replace(/\s+/g, '-')}.md`; // 生成文件路径
    const tagsArray = tags.split(',').map(tag => tag.trim()); // 将标签字符串转换为数组
    
    // 使用 encodeURIComponent 和 btoa 进行编码
    const contentToEncode = `---\ntitle: "${title}"\nauthor: "${authorName}"\nauthorImage: "${authorImage}"\ntags: [${tagsArray.map(tag => `"${tag}"`).join(', ')}]\n---\n\n${content}`;
    const encodedContent = btoa(unescape(encodeURIComponent(contentToEncode)));

    const data = {
        message: `Add blog post: ${title}`,
        content: encodedContent, // 使用编码后的内容
        branch: BRANCH,
    };

    try {
        const response = await axios.put(
            `https://api.github.com/repos/${REPO_OWNER}/${REPO_NAME}/contents/${filePath}`,
            data,
            {
                headers: {
                    Authorization: `token ${GITHUB_TOKEN}`,
                    'Content-Type': 'application/json',
                },
            }
        );

        if (response.status === 201) {
            setMessage('文章提交成功！');
            setTitle('');
            setAuthorName('');
            setAuthorImage('');
            setTags('');
            setContent('');
        }
    } catch (error) {
        console.error('Error submitting post:', error);
        setMessage('提交文章失败，请检查控制台以获取更多信息。');
    } finally {
        setLoading(false);
    }
};


  return (
    <form onSubmit={handleSubmit}>
      <h1>发布博客</h1>
      <div>
        <label>
          文章标题:
          <input
            type="text"
            value={title}
            onChange={(e) => setTitle(e.target.value)}
            required
          />
        </label>
      </div>
      <div>
        <label>
          作者名:
          <input
            type="text"
            value={authorName}
            onChange={(e) => setAuthorName(e.target.value)}
            required
          />
        </label>
      </div>
      <div>
        <label>
          作者图像 URL:
          <input
            type="text"
            value={authorImage}
            onChange={(e) => setAuthorImage(e.target.value)}
            required
          />
        </label>
      </div>
      <div>
        <label>
          文章标签 (用逗号分隔):
          <input
            type="text"
            value={tags}
            onChange={(e) => setTags(e.target.value)}
            required
          />
        </label>
      </div>
      <div>
        <label>
          文章内容 (Markdown):
          <MarkdownEditor
            value={content}
            style={{ height: '300px' }}
            renderHTML={(text) => mdParser.render(text)}
            onChange={handleEditorChange}
          />
        </label>
      </div>
      <button type="submit" disabled={loading}>
        {loading ? '提交中...' : '提交文章'}
      </button>
      {message && <p>{message}</p>}
    </form>
  );
}

function SubmitPostPage() {
  return (
    <Layout title="发布博客" description="提交你的博客文章">
      <main className='submit-post-container'>
        <SubmitPostForm />
      </main>
    </Layout>
  );
}

export default SubmitPostPage;

