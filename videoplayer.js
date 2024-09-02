import React, { useEffect, useRef } from 'react';
import './node_modules/xgplayer/dist/index.min.css';
import XgPlayer from 'xgplayer';

export default function VideoPlayer({src}) {
  const playerRef = useRef(null); // 创建一个 ref 用于指向播放器的 DOM 元素

  useEffect(() => {
    const player = new XgPlayer({
      id: 'video-player', // 确保 id 是唯一的
      url: src,
      el: playerRef.current, // 将 ref 传递给播放器
      autoplay: false, // 自动播放
      controls: true,
      fluid: true, // 使播放器自适应宽高
    });

    return () => {
      player.destroy(); // 清理播放器实例，避免内存泄漏
    };
  }, [src]);

  return (
    <div>
      <div id='video-player' ref={playerRef} style={{ width: '100%', height: 'auto' }}/> {/* 为播放器提供一个容器 */}
    </div>
  );
}
