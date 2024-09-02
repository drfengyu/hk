import React from 'react';

import TwikooComment from '@site/TwikooComment';
export default function BlogPostItemContainer({
  children,
  className,
  list,
}) {
  return <>

  <article className={className}>{children}</article>;
  {!list && <TwikooComment />}
  </>;

}

