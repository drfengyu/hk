import React, { useEffect, useRef } from 'react';
export default function TwikooComment({ slug }) {
  const slugRef = useRef(null);

  useEffect(() => {
    const script = document.createElement('script');
    script.src = 'https://cdn.jsdelivr.net/npm/twikoo@1.6.39/dist/twikoo.all.min.js';
    script.async = true; // 异步加载脚本
    script.onload = () => {
      
      // 确保 twikoo 已经加载完毕
      
      if (window.twikoo) {      
        window.twikoo.init({
          envId: 'https://twikoo.drfengling.online/',
          el:slugRef.current,
        }); 
      }
    }
    document.body.appendChild(script);
    return () => {
      // 清理脚本
      document.body.removeChild(script);
    };
  }, []);

  return (
    <div>
      <div ref={slugRef}/>
    </div>
  );
}

