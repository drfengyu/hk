// src/components/SubmitPostLayout.js

import React from 'react';
import Layout from '@theme/Layout';
import SubmitPostForm from '@site/src/pages/submit-post';

function SubmitPostLayout() {
  return (
    <Layout title="发布博客" description="提交你的博客文章">
      <main>
        <div style={{ maxWidth: '800px', margin: '0 auto', padding: '20px' }}>
          <h1>发布博客</h1>
          <SubmitPostForm />
        </div>
      </main>
    </Layout>
  );
}

export default SubmitPostLayout;
