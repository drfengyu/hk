"use strict";(self.webpackChunkmy_website=self.webpackChunkmy_website||[]).push([[4813],{83878:(e,t,n)=>{n.d(t,{A:()=>i});var a=n(96540),s=n(74848);function i(e){let{slug:t}=e;const n=(0,a.useRef)(null);return(0,a.useEffect)((()=>{const e=document.createElement("script");return e.src="https://cdn.jsdelivr.net/npm/twikoo@1.6.39/dist/twikoo.all.min.js",e.async=!0,e.onload=()=>{window.twikoo&&window.twikoo.init({envId:"https://twikoo.drfengling.online/",el:n.current})},document.body.appendChild(e),()=>{document.body.removeChild(e)}}),[]),(0,s.jsx)("div",{children:(0,s.jsx)("div",{ref:n})})}},47713:(e,t,n)=>{n.d(t,{A:()=>r});n(96540);var a=n(21312),s=n(39022),i=n(74848);function r(e){const{metadata:t}=e,{previousPage:n,nextPage:r}=t;return(0,i.jsxs)("nav",{className:"pagination-nav","aria-label":(0,a.T)({id:"theme.blog.paginator.navAriaLabel",message:"Blog list page navigation",description:"The ARIA label for the blog pagination"}),children:[n&&(0,i.jsx)(s.A,{permalink:n,title:(0,i.jsx)(a.A,{id:"theme.blog.paginator.newerEntries",description:"The label used to navigate to the newer blog posts page (previous page)",children:"Newer Entries"})}),r&&(0,i.jsx)(s.A,{permalink:r,title:(0,i.jsx)(a.A,{id:"theme.blog.paginator.olderEntries",description:"The label used to navigate to the older blog posts page (next page)",children:"Older Entries"}),isNext:!0})]})}},33069:(e,t,n)=>{n.r(t),n.d(t,{default:()=>b});n(96540);var a=n(34164),s=n(21312),i=n(61213),r=n(17559),l=n(96461),o=n(28774),c=n(28027),d=n(47713),g=n(41463),u=n(72852),m=n(32234),h=n(51107),p=n(74848);function x(e){let{tag:t}=e;const n=(0,l.ZD)(t);return(0,p.jsxs)(p.Fragment,{children:[(0,p.jsx)(i.be,{title:n,description:t.description}),(0,p.jsx)(g.A,{tag:"blog_tags_posts"})]})}function j(e){let{tag:t,items:n,sidebar:a,listMetadata:i}=e;const r=(0,l.ZD)(t);return(0,p.jsxs)(c.A,{sidebar:a,children:[t.unlisted&&(0,p.jsx)(m.A,{}),(0,p.jsxs)("header",{className:"margin-bottom--xl",children:[(0,p.jsx)(h.A,{as:"h1",children:r}),t.description&&(0,p.jsx)("p",{children:t.description}),(0,p.jsx)(o.A,{href:t.allTagsPath,children:(0,p.jsx)(s.A,{id:"theme.tags.tagsPageLink",description:"The label of the link targeting the tag list page",children:"View All Tags"})})]}),(0,p.jsx)(u.A,{items:n}),(0,p.jsx)(d.A,{metadata:i})]})}function b(e){return(0,p.jsxs)(i.e3,{className:(0,a.A)(r.G.wrapper.blogPages,r.G.page.blogTagPostListPage),children:[(0,p.jsx)(x,{...e}),(0,p.jsx)(j,{...e})]})}},32234:(e,t,n)=>{n.d(t,{A:()=>c});n(96540);var a=n(34164),s=n(44084),i=n(17559),r=n(27293),l=n(74848);function o(e){let{className:t}=e;return(0,l.jsx)(r.A,{type:"caution",title:(0,l.jsx)(s.Rc,{}),className:(0,a.A)(t,i.G.common.unlistedBanner),children:(0,l.jsx)(s.Uh,{})})}function c(e){return(0,l.jsxs)(l.Fragment,{children:[(0,l.jsx)(s.AE,{}),(0,l.jsx)(o,{...e})]})}},39022:(e,t,n)=>{n.d(t,{A:()=>r});n(96540);var a=n(34164),s=n(28774),i=n(74848);function r(e){const{permalink:t,title:n,subLabel:r,isNext:l}=e;return(0,i.jsxs)(s.A,{className:(0,a.A)("pagination-nav__link",l?"pagination-nav__link--next":"pagination-nav__link--prev"),to:t,children:[r&&(0,i.jsx)("div",{className:"pagination-nav__sublabel",children:r}),(0,i.jsx)("div",{className:"pagination-nav__label",children:n})]})}},56133:(e,t,n)=>{n.d(t,{A:()=>l});n(96540);var a=n(34164),s=n(28774);const i={tag:"tag_zVej",tagRegular:"tagRegular_sFm0",tagWithCount:"tagWithCount_h2kH"};var r=n(74848);function l(e){let{permalink:t,label:n,count:l,description:o}=e;return(0,r.jsxs)(s.A,{href:t,title:o,className:(0,a.A)(i.tag,l?i.tagWithCount:i.tagRegular),children:[n,l&&(0,r.jsx)("span",{children:l})]})}},62053:(e,t,n)=>{n.d(t,{A:()=>o});n(96540);var a=n(34164),s=n(21312),i=n(56133);const r={tags:"tags_jXut",tag:"tag_QGVx"};var l=n(74848);function o(e){let{tags:t}=e;return(0,l.jsxs)(l.Fragment,{children:[(0,l.jsx)("b",{children:(0,l.jsx)(s.A,{id:"theme.tags.tagsListLabel",description:"The label alongside a tag list",children:"Tags:"})}),(0,l.jsx)("ul",{className:(0,a.A)(r.tags,"padding--none","margin-left--sm"),children:t.map((e=>(0,l.jsx)("li",{className:r.tag,children:(0,l.jsx)(i.A,{...e})},e.permalink)))})]})}},96461:(e,t,n)=>{n.d(t,{ZD:()=>r,uz:()=>l});n(96540);var a=n(21312),s=n(53465);n(74848);function i(){const{selectMessage:e}=(0,s.W)();return t=>e(t,(0,a.T)({id:"theme.blog.post.plurals",description:'Pluralized label for "{count} posts". Use as much plural forms (separated by "|") as your language support (see https://www.unicode.org/cldr/cldr-aux/charts/34/supplemental/language_plural_rules.html)',message:"One post|{count} posts"},{count:t}))}function r(e){const t=i();return(0,a.T)({id:"theme.blog.tagTitle",description:"The title of the page for a blog tag",message:'{nPosts} tagged with "{tagName}"'},{nPosts:t(e.count),tagName:e.label})}const l=()=>(0,a.T)({id:"theme.blog.authorsList.pageTitle",message:"Authors",description:"The title of the authors page"})},44084:(e,t,n)=>{n.d(t,{AE:()=>o,Rc:()=>r,TT:()=>d,Uh:()=>l,Yh:()=>c});n(96540);var a=n(21312),s=n(5260),i=n(74848);function r(){return(0,i.jsx)(a.A,{id:"theme.contentVisibility.unlistedBanner.title",description:"The unlisted content banner title",children:"Unlisted page"})}function l(){return(0,i.jsx)(a.A,{id:"theme.contentVisibility.unlistedBanner.message",description:"The unlisted content banner message",children:"This page is unlisted. Search engines will not index it, and only users having a direct link can access it."})}function o(){return(0,i.jsx)(s.A,{children:(0,i.jsx)("meta",{name:"robots",content:"noindex, nofollow"})})}function c(){return(0,i.jsx)(a.A,{id:"theme.contentVisibility.draftBanner.title",description:"The draft content banner title",children:"Draft page"})}function d(){return(0,i.jsx)(a.A,{id:"theme.contentVisibility.draftBanner.message",description:"The draft content banner message",children:"This page is a draft. It will only be visible in dev and be excluded from the production build."})}},97800:(e,t,n)=>{n.d(t,{A:()=>B});n(96540);var a=n(34164),s=n(44096),i=n(83878),r=n(74848);function l(e){let{children:t,className:n,list:a}=e;return(0,r.jsxs)(r.Fragment,{children:[(0,r.jsx)("article",{className:n,children:t}),";",!a&&(0,r.jsx)(i.A,{})]})}var o=n(28774);const c={title:"title_f1Hy"};function d(e){let{className:t}=e;const{metadata:n,isBlogPostPage:i}=(0,s.e7)(),{permalink:l,title:d}=n,g=i?"h1":"h2";return(0,r.jsx)(g,{className:(0,a.A)(c.title,t),children:i?d:(0,r.jsx)(o.A,{to:l,children:d})})}var g=n(21312),u=n(53465),m=n(36266);const h={container:"container_mt6G"};function p(e){let{readingTime:t}=e;const n=function(){const{selectMessage:e}=(0,u.W)();return t=>{const n=Math.ceil(t);return e(n,(0,g.T)({id:"theme.blog.post.readingTime.plurals",description:'Pluralized label for "{readingTime} min read". Use as much plural forms (separated by "|") as your language support (see https://www.unicode.org/cldr/cldr-aux/charts/34/supplemental/language_plural_rules.html)',message:"One min read|{readingTime} min read"},{readingTime:n}))}}();return(0,r.jsx)(r.Fragment,{children:n(t)})}function x(e){let{date:t,formattedDate:n}=e;return(0,r.jsx)("time",{dateTime:t,children:n})}function j(){return(0,r.jsx)(r.Fragment,{children:" \xb7 "})}function b(e){let{className:t}=e;const{metadata:n}=(0,s.e7)(),{date:i,readingTime:l}=n,o=(0,m.i)({day:"numeric",month:"long",year:"numeric",timeZone:"UTC"});return(0,r.jsxs)("div",{className:(0,a.A)(h.container,"margin-vert--md",t),children:[(0,r.jsx)(x,{date:i,formattedDate:(c=i,o.format(new Date(c)))}),void 0!==l&&(0,r.jsxs)(r.Fragment,{children:[(0,r.jsx)(j,{}),(0,r.jsx)(p,{readingTime:l})]})]});var c}var f=n(56913);const A={authorCol:"authorCol_Hf19",imageOnlyAuthorRow:"imageOnlyAuthorRow_pa_O",imageOnlyAuthorCol:"imageOnlyAuthorCol_G86a"};function v(e){let{className:t}=e;const{metadata:{authors:n},assets:i}=(0,s.e7)();if(0===n.length)return null;const l=n.every((e=>{let{name:t}=e;return!t})),o=1===n.length;return(0,r.jsx)("div",{className:(0,a.A)("margin-top--md margin-bottom--sm",l?A.imageOnlyAuthorRow:"row",t),children:n.map(((e,t)=>(0,r.jsx)("div",{className:(0,a.A)(!l&&(o?"col col--12":"col col--6"),l?A.imageOnlyAuthorCol:A.authorCol),children:(0,r.jsx)(f.A,{author:{...e,imageURL:i.authorsImageUrls[t]??e.imageURL}})},t)))})}function T(){return(0,r.jsxs)("header",{children:[(0,r.jsx)(d,{}),(0,r.jsx)(b,{}),(0,r.jsx)(v,{})]})}var w=n(70440),N=n(12125);function _(e){let{children:t,className:n}=e;const{isBlogPostPage:i}=(0,s.e7)();return(0,r.jsx)("div",{id:i?w.LU:void 0,className:(0,a.A)("markdown",n),children:(0,r.jsx)(N.A,{children:t})})}var k=n(17559),y=n(4336),P=n(62053);function R(){return(0,r.jsx)("b",{children:(0,r.jsx)(g.A,{id:"theme.blog.post.readMore",description:"The label used in blog post item excerpts to link to full blog posts",children:"Read More"})})}function U(e){const{blogPostTitle:t,...n}=e;return(0,r.jsx)(o.A,{"aria-label":(0,g.T)({message:"Read more about {title}",id:"theme.blog.post.readMoreLabel",description:"The ARIA label for the link to full blog posts from excerpts"},{title:t}),...n,children:(0,r.jsx)(R,{})})}function C(){const{metadata:e,isBlogPostPage:t}=(0,s.e7)(),{tags:n,title:i,editUrl:l,hasTruncateMarker:o,lastUpdatedBy:c,lastUpdatedAt:d}=e,g=!t&&o,u=n.length>0;if(!(u||g||l))return null;if(t){const e=!!(l||d||c);return(0,r.jsxs)("footer",{className:"docusaurus-mt-lg",children:[u&&(0,r.jsx)("div",{className:(0,a.A)("row","margin-top--sm",k.G.blog.blogFooterEditMetaRow),children:(0,r.jsx)("div",{className:"col",children:(0,r.jsx)(P.A,{tags:n})})}),e&&(0,r.jsx)(y.A,{className:(0,a.A)("margin-top--sm",k.G.blog.blogFooterEditMetaRow),editUrl:l,lastUpdatedAt:d,lastUpdatedBy:c})]})}return(0,r.jsxs)("footer",{className:"row docusaurus-mt-lg",children:[u&&(0,r.jsx)("div",{className:(0,a.A)("col",{"col--9":g}),children:(0,r.jsx)(P.A,{tags:n})}),g&&(0,r.jsx)("div",{className:(0,a.A)("col text--right",{"col--3":u}),children:(0,r.jsx)(U,{blogPostTitle:i,to:e.permalink})})]})}function B(e){let{children:t,className:n,list:i}=e;const o=function(){const{isBlogPostPage:e}=(0,s.e7)();return e?void 0:"margin-bottom--xl"}();return(0,r.jsxs)(l,{className:(0,a.A)(o,n),list:i,children:[(0,r.jsx)(T,{}),(0,r.jsx)(_,{children:t}),(0,r.jsx)(C,{})]})}},72852:(e,t,n)=>{n.d(t,{A:()=>r});n(96540);var a=n(44096),s=n(97800),i=n(74848);function r(e){let{items:t,component:n=s.A}=e;return(0,i.jsx)(i.Fragment,{children:t.map((e=>{let{content:t}=e;return(0,i.jsx)(a.in,{content:t,children:(0,i.jsx)(n,{list:!0,children:(0,i.jsx)(t,{})})},t.metadata.permalink)}))})}}}]);