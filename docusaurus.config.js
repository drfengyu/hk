// @ts-check
// `@type` JSDoc annotations allow editor autocompletion and type checking
// (when paired with `@ts-check`).
// There are various equivalent ways to declare your Docusaurus config.
// See: https://docusaurus.io/docs/api/docusaurus-config

import {themes as prismThemes} from 'prism-react-renderer';

/** @type {import('@docusaurus/types').Config} */
const config = {
  title: '海康视觉学习',
  tagline: '海康视觉学习笔记',
  favicon: 'img/favicon.ico',

  // Set the production url of your site here
  url: 'https://your-docusaurus-site.example.com',
  // Set the /<baseUrl>/ pathname under which your site is served
  // For GitHub pages deployment, it is often '/<projectName>/'
  baseUrl: '/hk/',

  // GitHub pages deployment config.
  // If you aren't using GitHub pages, you don't need these.
  organizationName: 'drfengyu', // Usually your GitHub org/user name.
  projectName: 'hk', // Usually your repo name.

  onBrokenLinks: 'throw',
  onBrokenMarkdownLinks: 'warn',

  // Even if you don't use internationalization, you can use this field to set
  // useful metadata like html lang. For example, if your site is Chinese, you
  // may want to replace "en" with "zh-Hans".
  i18n: {
    defaultLocale: 'zh-Hans',
    locales: ['zh-Hans'],
  },

  presets: [
    [
      'classic',
      /** @type {import('@docusaurus/preset-classic').Options} */
      ({
        docs: {
          sidebarPath: './sidebars.js',
          // Please change this to your repo.
          // Remove this to remove the "edit this page" links.
          editUrl:
            'https://github.com/drfengyu/hk/tree/gh-pages/',
        },
        
        blog: {
          showReadingTime: true,
          feedOptions: {
            type: ['rss', 'atom'],
            xslt: true,
          },
          // Please change this to your repo.
          // Remove this to remove the "edit this page" links.
          editUrl:
            'https://github.com/drfengyu/hk/tree/gh-pages/',
        },
        theme: {
          customCss: './src/css/custom.css',
        },
      }),
    ],
  ],

  themeConfig:
    /** @type {import('@docusaurus/preset-classic').ThemeConfig} */
    ({
      // Replace with your project's social card
      image: 'img/docusaurus-social-card.jpg',
      navbar: {
        title: '海康视觉',
        logo: {
          alt: 'My Site Logo',
          src: 'img/logo.svg',
        },
        items: [
          {
            type: 'docSidebar',
            sidebarId: 'tutorialSidebar',
            position: 'left',
            label: '教程',
          },
          // {to: '/submit-post', label: '发布', position: 'left'},
           {to: 'blog/chat', label: '留言板', position: 'right'},
          // {
          //   to: 'ai',
          //   label: 'Sign in to chat with AI free ',
          //   position: 'right',
          // },
          {
            href: 'https://github.com/drfengyu/hk',
            label: 'GitHub',
            position: 'right',
          },
        ],
      },
      footer: {
        style: 'dark',
        links: [
          {
            title: '文档',
            items: [
              {
                label: '教程',
                to: '/docs/vm-usage-tutorial/master-various-vm-modules/software-installation-tutorial',
              },
            ],
          },
          {
            title: '联系',
            items: [
              {
                label: 'CSDN',
                href: 'https://blog.csdn.net/qq_44082700/category_12759515.html',
              },
              {
                label: 'Email',
                href:'mailto:zhh@drfengling.online',
              },
            ],
          },
          {
            title: '更多',
            items: [
              
              {
                label: 'GitHub',
                href: 'https://github.com/drfengyu/hk',
              },
              {
                label: 'drfengling.online',
                href: 'https://drfengling.online',
              },
            ],
          },
          {
            title: '友链',
            items: [
              {
                label: 'docusaurus',
                href:'https://docusaurus.io/zh-CN/docs#fast-track',
              },
              {
                label: 'twikoo',
                href:'https://twikoo.js.org/',
              },
            ],
          },
        ],
        copyright: `Copyright © ${new Date().getFullYear()} Fengling, Inc. Built with Docusaurus.`,
      },
      prism: {
        theme: prismThemes.github,
        darkTheme: prismThemes.dracula,
      },
    }),
};

export default config;
